#include "generate.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "openssl/sha.h"

std::string sha256(const std::string &inputStr) {
  unsigned char hash[SHA256_DIGEST_LENGTH];
  const unsigned char *data = (const unsigned char *)inputStr.c_str();
  SHA256(data, inputStr.size(), hash);
  std::stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
  }
  return ss.str();
}
