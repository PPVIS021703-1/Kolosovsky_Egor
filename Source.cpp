#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "long.h"

using namespace std;

int main(int argc, char* argv[])
{
    std::string num;
    cout << "Input first number\n";
    cin >> num;
    LongInt a(num);
    cout << "Input second number\n";
    cin >> num;
    LongInt b = num;
    cout << "X: " << a << "\n" << "Y: " << b << "\n";
    cout << "X == Y: " << (a == b) << "\n";
    cout << "X - Y: " << a - b << "\n";
    cout << "X + Y: " << a + b << "\n";
    a++; b--; --b; ++a;
    cout << "X++ ++X: " << a << "\n" << "Y-- --Y: " << b << "\n";
    a -= 17; b += 17;
    cout << "X -= 17: " << a << "\n" << "Y += 17: " << b << "\n";
    cout << "X + 25 == X - 25: " << ((b + 25) == (a - 25)) << "\n";
    cout << "\n\n" << "X: " << a << "\n" << "Y: " << b << "\n";
    cout << "X * 3255: " << a * 3255 << "\n";
    cout << "X * Y: " << a * b << "\n";
    cout << "X / 125: " << a / 125 << "\n";
    cout << "X / Y: " << a / b << "\n";
    cout << "X % Y: " << a % b << "\n";
  
    return 0;
}