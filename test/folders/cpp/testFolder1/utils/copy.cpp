#include <exception>
#include <iostream>
using namespace std;

void copy(int num) {
  cout << num;
  throw std::invalid_argument(
      "This is some invalid args exception: %%globalException%%");
}
