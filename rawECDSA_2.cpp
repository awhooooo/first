#include "rawECDSA.h"
#include <bitcoin/system.hpp>
#include <boost/endian/conversion.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

using namespace boost::multiprecision;
using namespace libbitcoin;
using namespace libbitcoin::wallet;
using namespace libbitcoin::machine;
using namespace libbitcoin::chain;
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

std::string toHexString(const std::vector<uint8_t>& data) {
    std::ostringstream oss;
    // Set up the stream to format the output in hexadecimal and fill with zeros if needed
    oss << std::hex << std::setfill('0');
    for (auto byte : data) {
        // Each byte is formatted to be exactly two characters wide
        oss << std::setw(2) << static_cast<int>(byte);
    }
    return oss.str();
}

int testing_ECDSA()
{
    ECDSA::is_on_curve(ECDSA::G);

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
    // testing_ECDSA();

    wallet::ec_private privateKey("secret for obvious reason");
    wallet::payment_address from_address("1EKzgpZGX2zBxeWw5Dw5zMGYHVUiV21MZP");
    wallet::payment_address to_address("16vnUfDxdMWYKYpw4gCqkwCHRy7jtzgJgn");

    uint32_t version = 2;
    uint8_t input_count = 2;
    uint256_t tx_hash1 = uint256_t("0x1b76e40fa71c226ccbdb9f430fa21f1f341579c0f22fd4fc256eee0faf423982");
    uint256_t tx_hash2 = uint256_t("0x72a686bb332c97c590f4e1dbcb1cb08d50ab75dbdd2b09d0eb2bf7fee8fc7f6f");
    uint32_t tx_pos1 = 0;
    uint32_t tx_pos2 = 0;
    script input_script = script().to_pay_key_hash_pattern(from_address.hash());
    uint32_t nSequence = 0xffffffff;

    uint8_t output_count = 1;
    uint64_t output_value = 1999800 - 400;
    script output_script = script().to_pay_key_hash_pattern(to_address.hash());
    uint32_t nLocktime = 0;
    uint32_t sighash_ALL = 1;

    std::cout << std::endl;
    std::cout << "Version:               " << toHexString(version, false) << std::endl;
    std::cout << "Input Count:           " << toHexString(input_count, false) <<std::endl;
    std::cout << "Input 1 Tx Hash:       " << toHexString(tx_hash1, true) <<std::endl;
    std::cout << "Input 1 Tx Pos:        " << toHexString(tx_pos1, false) <<std::endl;
    std::cout << "Input 1 scriptPubKey:  " << toHexString(input_script.to_data(0)) << std::endl;
    std::cout << "Input 2 Tx Hash:       " << toHexString(tx_hash2, true) <<std::endl;
    std::cout << "Input 2 Tx Pos:        " << toHexString(tx_pos2, false) <<std::endl;
    std::cout << "Input 2 scriptPubKey:  " << toHexString(input_script.to_data(0)) << std::endl;
    std::cout << "nSequence:             " << toHexString(nSequence, false) << std::endl;
    std::cout << "Output Count:          " << toHexString(output_count, false) << std::endl;
    std::cout << "Output Value:          " << toHexString(output_value, false) << std::endl;
    std::cout << "Output scriptPubKey:   " << toHexString(output_script.to_data(0)) << std::endl;
    std::cout << "nLocktime:             " << toHexString(nLocktime, false) << std::endl;
    std::cout << "Sighash Code:          " << toHexString(sighash_ALL, false) << std::endl;

    std::string tx_preimage1 = toHexString(version, false) + toHexString(input_count, false) + toHexString(tx_hash1, false) + \
                               toHexString(tx_pos1, false) + varint(toHexString(input_script.to_data(0))) + toHexString(input_script.to_data(0)) + \
                               toHexString(nSequence, false) + toHexString(tx_hash2, false) + toHexString(tx_pos2, false) + "00" + \
                               toHexString(nSequence, false) + toHexString(output_count, false) + toHexString(output_value, false) + \
                               varint(toHexString(output_script.to_data(0))) + toHexString(output_script.to_data(0)) + \
                               toHexString(nLocktime, false) + toHexString(sighash_ALL, false);

    std::string tx_preimage2 = toHexString(version, false) + toHexString(input_count, false) + toHexString(tx_hash1, false) + \
                               toHexString(tx_pos1, false) + "00" + toHexString(nSequence, false) + toHexString(tx_hash2, false) + 
                               toHexString(tx_pos2, false) + varint(toHexString(input_script.to_data(0))) + toHexString(input_script.to_data(0)) + \
                               toHexString(nSequence, false) + toHexString(output_count, false) + toHexString(output_value, false) + \
                               varint(toHexString(output_script.to_data(0))) + toHexString(output_script.to_data(0)) + \
                               toHexString(nLocktime, false) + toHexString(sighash_ALL, false);

    std::cout << std::endl;
    std::cout << "Transaction Preimage 1:" << tx_preimage1 << std::endl;
    std::cout << std::endl;
    std::cout << "Transaction Preimage 2:" << tx_preimage2 << std::endl;
    
    OptionalPoint signature1 = ECDSA::sign_message(cpp_int(privateKey.secret()), tx_preimage1);
    OptionalPoint signature2 = ECDSA::sign_message(cpp_int(privateKey.secret()), tx_preimage2);
    OptionalPoint pubkey = ECDSA::scalar_mult(cpp_int(privateKey.secret()), ECDSA::G);
    assert(ECDSA::verify_signature(pubkey, tx_preimage1, signature1) == true);
    assert(ECDSA::verify_signature(pubkey, tx_preimage2, signature2) == true);

    std::string Der_signature1 = ECDSA::der(signature1) + "01";
    std::string Der_signature2 = ECDSA::der(signature2) + "01";
    std::string compressed_pubkey = privateKey.to_public().encoded();
    std::string scriptSig1 = varint(Der_signature1) + Der_signature1 + varint(compressed_pubkey) + compressed_pubkey;
    std::string scriptSig2 = varint(Der_signature2) + Der_signature2 + varint(compressed_pubkey) + compressed_pubkey;

    std::string transaction = toHexString(version, false) + toHexString(input_count, false) + toHexString(tx_hash1, false) + \
                              toHexString(tx_pos1, false) + varint(scriptSig1) + scriptSig1 + toHexString(nSequence, false) + \
                              toHexString(tx_hash2, false) + toHexString(tx_pos2, false) + varint(scriptSig2) + scriptSig2 +  \
                              toHexString(nSequence, false) + toHexString(output_count, false) + toHexString(output_value, false) + \
                              varint(toHexString(output_script.to_data(0))) + toHexString(output_script.to_data(0)) + \
                              toHexString(nLocktime, false);

    std::cout << std::endl;
    std::cout << "Raw Transaction:      " << transaction << std::endl;

    return 0;
}
