#include <iostream>
using namespace std;
int main(){
    try {
        cout << "Hello World";
    } catch(exception& e) {
        cout << "Some boring exception";
    } catch (...) {
        cout << "Inside exception";
    }
    return 0;
}
