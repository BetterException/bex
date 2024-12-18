#include <exception>
#include <iostream>
#include <string>

int add(std::string num1, std::string num2) {
  int _num1 = 0, _num2 = 0;
  try {
    _num1 = std::stoi(num1);
    _num2 = std::stoi(num2);
    return _num1 + _num2;
  } catch (const std::exception& e) {
    throw new std::runtime_error("Arguments are invalid: ~exception~");
  }
}
