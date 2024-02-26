#ifndef COMPLEX_H_
#define COMPLEX_H_

namespace COMPLEX
{
    class Complex
    {
        private:
            double x;
            double y;

        public:
            Complex();
            Complex(double re, double im);
            ~Complex();
            void show_coor() const;
            double show_Re() const { return x; }
            double show_Im() const { return y; }
            double size() const;

            Complex operator+(const Complex & c) const;
            Complex operator-(const Complex & c) const;
            Complex operator-() const;
            Complex operator~() const;
            Complex operator*(double n) const;
            Complex operator*(const Complex & c);

            friend Complex operator*(double n, const Complex & c);
            friend std::ostream & operator<<(std::ostream & os, const Complex & c);
            friend std::istream & operator>>(std::istream & is, Complex & c);
    };
};

#endif