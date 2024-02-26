#include <iostream>
#include "chapter11_7.h"

// macOS github testing now

namespace COMPLEX
{
    Complex::Complex()
    {
        x = y = 0;
    }

    Complex::Complex(double re, double im)
    {
        x = re; y = im;
    }

    Complex::~Complex()
    {

    }

    void Complex::show_coor() const
    {
        std::cout << "(" << x << ", " << y << "i" << ")" << std::endl;
    }

    double Complex::size() const
    {
        return x * x + y * y;
    }

    Complex Complex::operator+(const Complex & c) const
    {
        return Complex(x + c.x, y + c.y);
    }

    Complex Complex::operator-(const Complex & c) const
    {
        return Complex(x - c.x, y - c.y);
    }

    Complex Complex::operator-() const
    {
        return Complex(-x, -y);
    }

    Complex Complex::operator~() const
    {
        return Complex(x, -y);
    }

    Complex Complex::operator*(double n) const
    {
        return Complex(n * x, n * y);
    }

    // friend method 에서는 Complex:: 가 안 붙음
    Complex operator*(double n, const Complex & c)
    {
        return c * n;
    }

    Complex Complex::operator*(const Complex & c)
    {
        return Complex(x * c.x - y * c.y, x * c.y + y * c.x);
    }

    std::ostream & operator<<(std::ostream & os, const Complex & c)
    {
        os << "(" << c.x << ", " << c.y << "i" << ")";
        return os;
    }

    std::istream & operator>>(std::istream & is, Complex & c)
    {
        is >> c.x >> c.y;
        return is;
    }
};
