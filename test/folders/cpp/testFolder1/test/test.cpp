#include <iostream>
using namespace std;

void test() {
  cout << "This shouldn't execute: !%%globalException%%\n";
  cout << "While this should: %%globalException%%\n";
  cout << "But this shouldn't: !%%global Exception%%\n";
}
