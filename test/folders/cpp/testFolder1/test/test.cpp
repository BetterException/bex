#include <iostream>
using namespace std;

void test() {
  cout << "This shouldn't execute: !%%globalException%%\n";
  cout << "While this should: 1972e4d0f3de2ddf76ddeb3e8cdf3009391d06eba0cf7ab705707827fc87ab03\n";
  cout << "But this shouldn't: !%%global Exception%%\n";
}
