#include "rawECDSA.h"
#include <boost/endian/conversion.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

using namespace boost::multiprecision;
using boost::multiprecision::uint256_t;

std::string varint(const std::string& value) {

    size_t byteLength = value.length() / 2;
    std::stringstream ss;
    ss << std::hex << std::setfill('0') << std::setw(2) << byteLength;
    return ss.str();
}

template<typename T>
std::string toHexString(const T& value, bool big_endian = true) {

    std::vector<unsigned char> bytes(sizeof(value), 0);
    for (size_t i = 0; i < bytes.size(); ++i) {
        bytes[i] = static_cast<unsigned char>((value >> (i * 8)) & 0xFF);
    }

    // Prepare to output as a hex string
    std::stringstream ss;
    ss << std::hex << std::setfill('0');

    if (big_endian) {
        // Output bytes in reverse order for big-endian
        for (auto it = bytes.rbegin(); it != bytes.rend(); ++it) {
            ss << std::setw(2) << static_cast<int>(*it);
        }
    } else {
        // Output bytes in normal order for little-endian
        for (auto it = bytes.begin(); it != bytes.end(); ++it) {
            ss << std::setw(2) << static_cast<int>(*it);
        }
    }
    return ss.str();
}

std::string toHexString(const uint256_t& value, bool big_endian = true) {

    std::vector<unsigned char> bytes(32, 0);
    for (size_t i = 0; i < bytes.size(); ++i) {
        bytes[i] = static_cast<unsigned char>((value >> (i * 8)) & 0xFF);
    }

    // Prepare to output as a hex string
    std::stringstream ss;
    ss << std::hex << std::setfill('0');

    if (big_endian) {
        // Output bytes in reverse order for big-endian
        for (auto it = bytes.rbegin(); it != bytes.rend(); ++it) {
            ss << std::setw(2) << static_cast<int>(*it);
        }
    } else {
        // Output bytes in normal order for little-endian
        for (auto it = bytes.begin(); it != bytes.end(); ++it) {
            ss << std::setw(2) << static_cast<int>(*it);
        }
    }
    return ss.str();
}

int testing_ECDSA()
{
    ECDSA::is_on_curve(ECDSA::G);
    // OptionalPoint dual = ECDSA::point_add(ECDSA::G, ECDSA::G);
    // std::cout << dual->first << " " << dual->second << std::endl;
    // OptionalPoint dddd = ECDSA::scalar_mult(2, ECDSA::G);
    // std::cout << dddd->first << " " << dddd->second << std::endl;

    std::pair<cpp_int, OptionalPoint> Keys = ECDSA::make_keypair();
    std::cout << "Private Key => " << Keys.first << std::endl;
    std::cout << "Public Key => " << Keys.second->first << "," << Keys.second->second << std::endl;
    
    std::string message = "Finished with my woman cause she couldn't help me with my mind.";
    OptionalPoint signature = ECDSA::sign_message(Keys.first, message);
    std::string DER = ECDSA::der(signature);
    std::cout << DER << std::endl;
    assert(ECDSA::verify_signature(Keys.second, message, signature));
    return 0;
}

int main()
{
    testing_ECDSA();
    uint32_t version = 2;
    uint8_t input_count = 1;
    uint256_t tx_hash = uint256_t("0xbbf64178121eef5ffe32399cb31c4dae14f685152784bea065d0e31b5a733764");
    uint32_t tx_pos = 0;
    uint32_t nSequence = 0xFFFFFFFD;

    uint8_t output_count = 1;
    uint64_t output_value = 100000000;
    uint32_t nLocktime = 0;

    std::cout << "Version Hex: " << toHexString(version, false) << std::endl;
    std::cout << "Input Count Hex: " << toHexString(input_count, false) <<std::endl;
    std::cout << "Tx Hash: " << toHexString(tx_hash, false) <<std::endl;
    std::cout << "Tx Pos: " << toHexString(tx_pos, false) <<std::endl;
    std::cout << "nSequence Hex: " << toHexString(nSequence, false) << std::endl;
    std::cout << "Output Count Hex: " << toHexString(output_count, false) << std::endl;
    std::cout << "Output Value Hex: " << toHexString(output_value, false) << std::endl;
    std::cout << "nLocktime Hex: " << toHexString(nLocktime, false) << std::endl;

    return 0;
}
