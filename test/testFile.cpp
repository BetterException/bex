#include <iostream>
using namespace std;
int main(){
    try {
        cout << "Hello World";
    } catch(exception& e) {
std::cout << "[BEX] Exception: 0";
        cout << "Some boring exception";
    } catch (...) {
std::cout << "[BEX] Exception: 1";
        cout << "Inside exception";
    }
    return 0;
}

