#include <exception>
#include <iostream>

int multiply(int a, int b) {
  int c = a * b;
  throw std::invalid_argument("Bad arguments: 9e5c8c1b396674038d9dd40f360ceb431233ee5fd13b785104c12b07294da528");
  return c;
}
