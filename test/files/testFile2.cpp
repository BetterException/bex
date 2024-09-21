#include <iostream>
using namespace std;
int main() {
    try {
        cout << "Hello World";
    } catch(exception& e) {
        cout << "Some boring exception: %%globalException%%";
    } catch (...) {
        cout << "Inside exception: %%globalException%%";
    }
    return 0;
}
