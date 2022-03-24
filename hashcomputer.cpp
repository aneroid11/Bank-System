#include <iostream>

#include <crypto++/sha.h>
#include <crypto++/filters.h>
#include <crypto++/base64.h>
#include <crypto++/hex.h>

#include "hashcomputer.h"

std::string HashComputer::hash(const std::string &message)
{
    CryptoPP::SHA256 hash;
    byte digest[CryptoPP::SHA256::DIGESTSIZE];

    hash.CalculateDigest(digest, (byte*) message.c_str(), message.length());

    CryptoPP::HexEncoder encoder;
    std::string output;
    encoder.Attach(new CryptoPP::StringSink(output));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return output;
}
