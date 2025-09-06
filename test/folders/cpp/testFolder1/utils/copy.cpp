#include <exception>
#include <iostream>
using namespace std;

void copy(int num) {
  cout << num;
  throw std::invalid_argument(
      "This is some invalid args exception: d539e0d36ff01a0ee1723d968c09d9f218388bfddc10d87781d242cb2d35ea40");
}
