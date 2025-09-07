#include "generate.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "openssl/sha.h"

std::string sha256(const std::string& inputStr) {
  unsigned char hash[SHA256_DIGEST_LENGTH];
  const auto data = reinterpret_cast<const unsigned char*>(inputStr.c_str());
  SHA256(data, inputStr.size(), hash);
  std::stringstream ss;
  for (const unsigned char i : hash) {
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i);
  }
  return ss.str();
}