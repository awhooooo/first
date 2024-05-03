#include "rawECDSA.h"
#include <openssl/sha.h>
#include <cassert>
#include <random>
#include <stdexcept>

using namespace boost::multiprecision;

// Returns the inverse of k modulo p.
// This function returns the only integer x such that (x * k) % p == 1.
// k must be non-zero and p must be a prime.
cpp_int ECDSA::inverse_mod(const cpp_int& k, const cpp_int& p) {
    assert(k != 0);

    cpp_int s = 0, old_s = 1;
    cpp_int t = 1, old_t = 0;
    cpp_int r = p, old_r = k;

    while (r != 0) {
        cpp_int quotient = old_r / r;
        std::swap(r, old_r -= quotient * r);
        std::swap(s, old_s -= quotient * s);
        std::swap(t, old_t -= quotient * t);
    }

    if (old_r == -1) {
        old_r = 1;
        old_s = -old_s;
        old_t = -old_t;
    }

    if (old_s < 0) 
        old_s += p;

    assert(abs(old_r) == 1);  // Ensure the gcd is exactly 1.
    cpp_int mod_check = (k * old_s) % p;
    if (mod_check < 0)
        mod_check += p;
    // std::cout << mod_check << std::endl;
    assert(mod_check % p == 1);  // Ensure the modular inverse property holds.

    return old_s;
}

// Returns True if the given point lies on the elliptic curve.
bool ECDSA::is_on_curve(const OptionalPoint& P1) {
    
    if (P1 == std::nullopt) {
        return true;
    }
    else {
        cpp_int x = P1->first;
        cpp_int y = P1->second;
        // std::cout << x << std::endl;
        // std::cout << y << std::endl;

        cpp_int lhs = (y * y) % ECDSA::p;
        cpp_int rhs = (x * x * x + ECDSA::b) % ECDSA::p;
        // std::cout << "LHS (y^2 mod p): " << lhs << std::endl;
        // std::cout << "RHS (x^3 + ax + b mod p): " << rhs << std::endl;

        return lhs == rhs;
    }
}

// Returns -point
OptionalPoint ECDSA::point_neg(const OptionalPoint& P1) {
    
    assert(ECDSA::is_on_curve(P1));

    if (P1 == std::nullopt) {
        return std::nullopt;
    }

    cpp_int x = P1->first;
    cpp_int y = P1->second;

    Point result = {x, -y % ECDSA::p};
    assert(ECDSA::is_on_curve(result));

    return result;
}

// Returns the result of point1 + point2 according to the group law
OptionalPoint ECDSA::point_add(const OptionalPoint& P1, const OptionalPoint& P2) {

    if (P1 == std::nullopt) {
        return P2;
    }
    else if (P2 == std::nullopt) {
        return P1;
    }
    else {
    
        assert(ECDSA::is_on_curve(P1));
        assert(ECDSA::is_on_curve(P2));

        cpp_int x1 = P1->first; cpp_int y1 = P1->second;
        cpp_int x2 = P2->first; cpp_int y2 = P2->second;
        cpp_int m;

        if (x1 == x2 && y1 != y2) {
            return std::nullopt;
        }
        else if (x1 == x2 && y1 == y2) {
            // Point doubling
            m = (3 * x1 * x1 + ECDSA::a) * inverse_mod(2 * y1, ECDSA::p);
        } 
        else {
            m = (y2 - y1) * inverse_mod(x2 - x1, ECDSA::p);
        }

        cpp_int x3 = (m * m - x1 - x2) % ECDSA::p;
        cpp_int y3 = (m * (x1 - x3) - y1) % ECDSA::p;
        if (y3 < 0) 
            y3 += ECDSA::p;  // Ensure y3 is always positive within the field

        return Point{x3, y3};
    }
}

// Returns k * point computed using the double and point_add algorithm
OptionalPoint ECDSA::scalar_mult(cpp_int k, const OptionalPoint& P1) {

    assert(ECDSA::is_on_curve(P1));
    if (k % ECDSA::n == 0 || P1 == std::nullopt) {
        return std::nullopt;
    }
    else if (k < 0) {
        return ECDSA::scalar_mult(-k, point_neg(P1));
    }

    OptionalPoint result = std::nullopt; 
    OptionalPoint addend = P1;

    while (k != cpp_int(0)) {
        if (k & 1) {
            result = ECDSA::point_add(result, addend);
        }
        addend = ECDSA::point_add(addend, addend);
        k >>= 1;
    }
    assert(ECDSA::is_on_curve(result));
    return result;
}

cpp_int ECDSA::generateRandomNumber(const cpp_int& max) {
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<uint64_t> distr;

    cpp_int result = 0;
    for (int i = 0; i < 4; ++i) {
        result <<= 64;
        result |= distr(eng);
    }

    // Ensure the number is within the range 1 to max-1
    std::cout << (result % (max - 1)) + 1 << std::endl;
    return (result % (max - 1)) + 1;
}

// Generates a random private-public key pair.
std::pair<cpp_int, OptionalPoint> ECDSA::make_keypair(void) {

    cpp_int privkey = ECDSA::generateRandomNumber(ECDSA::n);
    OptionalPoint pubkey = ECDSA::scalar_mult(privkey, ECDSA::G);
    std::pair<cpp_int, OptionalPoint> pair = {privkey, pubkey};

    return pair;
}

// Returns the truncated double SHA256 hash of the message.
cpp_int ECDSA::hash_message(const std::string& message) {
    
    std::vector<unsigned char> hash_input = ECDSA::string_to_binary(message);
    std::vector<unsigned char> hash_output = ECDSA::sha256(ECDSA::sha256(hash_input));
    std::string hex_output = ECDSA::binary_to_hex(hash_output);

    std::istringstream iss(hex_output);
    cpp_int result;
    iss >> std::hex >> result;

    return result;
}

OptionalPoint ECDSA::sign_message(cpp_int private_key, const std::string& message) {

    cpp_int z = ECDSA::hash_message(message);
    cpp_int r = 0; 
    cpp_int s = 0;

    while (!r || !s) {
        cpp_int k = ECDSA::generateRandomNumber(ECDSA::n);
        OptionalPoint P = ECDSA::scalar_mult(k, ECDSA::G);
        cpp_int x = P->first;
        cpp_int y = P->second;

        r = x % ECDSA::n;
        s = ((z + r * private_key) * ECDSA::inverse_mod(k, ECDSA::n)) % ECDSA::n;
    }

    return Point{r, s};
}

bool ECDSA::verify_signature(const OptionalPoint& public_key, const std::string& message, const OptionalPoint& signature) {

    cpp_int z = ECDSA::hash_message(message);
    cpp_int r = signature->first;
    cpp_int s = signature->second;

    cpp_int w = ECDSA::inverse_mod(s, ECDSA::n);
    cpp_int u1 = (z * w) % ECDSA::n;
    cpp_int u2 = (r * w) % ECDSA::n;

    OptionalPoint P1 = ECDSA::point_add(ECDSA::scalar_mult(u1, ECDSA::G), ECDSA::scalar_mult(u2, public_key));
    if ((r % ECDSA::n) == (P1->first % ECDSA::n)) {
        return true;
    }
    else {
        return false;
    }
}

std::string ECDSA::der(const OptionalPoint& P1) {

    cpp_int r = P1->first; cpp_int s = P1->second;

    // Ensure the "s" value is within the valid range
    if (s > (ECDSA::n / 2)) {
        s = ECDSA::n - s;
    }

    // Convert the r and s parts to bytes
    std::vector<unsigned char> rbin = ECDSA::cpp_into_bytes(r, true);
    std::vector<unsigned char> sbin = ECDSA::cpp_into_bytes(s, true);
    
    // If r or s bins have a high bit, add a 00
    if (rbin[0] >= 128) {
        rbin.insert(rbin.begin(), 0x00);
    }
    if (sbin[0] >= 128) {
        sbin.insert(sbin.begin(), 0x00);
    }

    // Start building the result with the 'r and s' part
    std::vector<unsigned char> result;
    result.reserve(3 + rbin.size() + sbin.size());
    result.push_back(0x30); // Initial header byte
    result.push_back(static_cast<unsigned char>(2 + rbin.size() + 2 + sbin.size())); // Total size of the content

    // Add rbin part
    result.push_back(0x02); // Header for rbin
    result.push_back(static_cast<unsigned char>(rbin.size())); // Size of rbin
    result.insert(result.end(), rbin.begin(), rbin.end()); // rbin content

    // Add sbin part
    result.push_back(0x02); // Header for sbin
    result.push_back(static_cast<unsigned char>(sbin.size())); // Size of sbin
    result.insert(result.end(), sbin.begin(), sbin.end()); // sbin content

    return ECDSA::binary_to_hex(result);
}

unsigned char ECDSA::hex_char_to_bin(char c) 
{
    if (c >= '0' && c <= '9') 
        return c - '0';
    if (c >= 'A' && c <= 'F') 
        return 10 + (c - 'A');
    if (c >= 'a' && c <= 'f') 
        return 10 + (c - 'a');
    throw std::invalid_argument("Invalid hexadecimal character");
}

// Convert string to binary data
std::vector<unsigned char> ECDSA::hexstring_to_binary(const std::string& hex) {
    std::vector<unsigned char> binary;
    if (hex.size() % 2 != 0) {
        throw std::invalid_argument("Hexadecimal string length must be even");
    }

    for (size_t i = 0; i < hex.size(); i += 2) {
        unsigned char high = ECDSA::hex_char_to_bin(hex[i]);
        unsigned char low = ECDSA::hex_char_to_bin(hex[i+1]);
        binary.push_back((high << 4) | low);
    }
    
    return binary;
}

// Convert binary data to hexadecimal string
std::string ECDSA::binary_to_hex(const std::vector<unsigned char>& binary_data) {

    std::stringstream hexstr;
    hexstr << std::hex << std::setfill('0');
    for (auto byte : binary_data) {
        hexstr << std::setw(2) << static_cast<int>(byte);
    }
    return hexstr.str();
}

// SHA-256 hashing function, processes binary data and returns binary data
std::vector<unsigned char> ECDSA::sha256(const std::vector<unsigned char>& data) {

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data.data(), data.size());
    SHA256_Final(hash, &sha256);

    return std::vector<unsigned char>(hash, hash + SHA256_DIGEST_LENGTH);
}

std::vector<unsigned char> ECDSA::cpp_into_bytes(const cpp_int& num, bool big_endian = true) {

    std::vector<unsigned char> bytes;
    if (big_endian) {
        // Export the number in big endian byte order
        export_bits(num, back_inserter(bytes), 8);
    } 
    else {
        // Export the number in little endian byte order
        export_bits(num, back_inserter(bytes), 8, false);
    }
    return bytes;
}
