#include <windows.h>
#include <iostream>
using namespace std;

int main() {
    char ch = 'A';
    int num = ch - '0' + 48;  // Subtracting the ASCII value of '0'
    
    cout << "The integer equivalent of " << ch << " is " << num << endl;
    return 0;
}