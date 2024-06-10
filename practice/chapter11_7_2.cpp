#include <iostream>
#include "chapter11_7.h"
using namespace std;
using namespace COMPLEX;

int main()
{
    Complex a(3, 4);
    a.show_coor();
    Complex c;
    cout << "Enter a complex number (q to quit):\n";
    while(cin >> c)
    {
        cout << "c is " << c << '\n';
        cout << "complex cojugate is " << ~c << '\n';
        cout << "a is " << a << '\n';
        cout << "a + c is " << a + c << '\n';
        cout << "a - c is " << a - c << '\n';
        cout << "a * c is " << a * c << '\n';
        cout << "2 * c is " << 2 * c << '\n';
        cout << "Enter a complex number (q to quit):\n";
    }
    cout << "TERMINATING...\n";

    return 0;
}
