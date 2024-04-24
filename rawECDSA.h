#ifndef ECDSA_H
#define ECDSA_H

#include <vector>
#include <cmath>
#include <string>
#include <utility>
#include <optional>
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;
using Point = std::pair<cpp_int, cpp_int>;
using OptionalPoint = std::optional<Point>;

class ECDSA
{
    public:
        inline static const cpp_int p = cpp_int("0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f");
        inline static const cpp_int a = 0;  // Considered cpp_int for consistency
        inline static const cpp_int b = 7;
        inline static const cpp_int h = 1;
        inline static const cpp_int n = cpp_int("0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141");
        inline static const Point G = {cpp_int("0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798"),
                                       cpp_int("0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8")};

        static cpp_int inverse_mod(const cpp_int& k, const cpp_int& p);
        static bool is_on_curve(const OptionalPoint& P1);
        static OptionalPoint point_neg(const OptionalPoint& P1);
        static OptionalPoint point_add(const OptionalPoint& P1, const OptionalPoint& P2);
        static OptionalPoint scalar_mult(cpp_int k, const OptionalPoint& P1);
        
        static cpp_int generateRandomNumber(const cpp_int& max);
        static std::pair<cpp_int, OptionalPoint> make_keypair(void);
        static cpp_int hash_message(const std::string& message);
        static OptionalPoint sign_message(cpp_int private_key, const std::string& message);
        static bool verify_signature(const OptionalPoint& public_key, const std::string& message, 
                                     const OptionalPoint& signature);
        static std::string der(const OptionalPoint& P1);

        static std::vector<unsigned char> string_to_binary(const std::string& str);
        static std::string binary_to_hex(const std::vector<unsigned char>& binary_data);
        static std::vector<unsigned char> sha256(const std::vector<unsigned char>& data);
        static std::vector<unsigned char> cpp_into_bytes(const cpp_int& num, bool big_endian);
};

#endif
