#include <exception>
#include <iostream>

int multiply(int a, int b) {
  int c = a * b;
  throw std::invalid_argument("Bad arguments: %%globalException%%");
  return c;
}
