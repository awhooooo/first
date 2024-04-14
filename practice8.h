#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>

namespace MATRIX
{
    class SquareMatrix
    {
        private:
            int dim;
            std::vector< std::vector<double> > v1;
        
        public:
            SquareMatrix(int dim) : dim(dim), v1(dim, std::vector<double>(dim, 0)) {}
            SquareMatrix(const SquareMatrix& M) : dim(M.dim), v1(M.v1) {}
            ~SquareMatrix() {}

            SquareMatrix operator+(const SquareMatrix& M) const;
            SquareMatrix operator-(const SquareMatrix& M) const;
            SquareMatrix operator-() const;
            SquareMatrix operator*(const SquareMatrix& M) const;
            SquareMatrix operator*(double n) const;

            SquareMatrix& operator+=(const SquareMatrix& M);
            SquareMatrix& operator-=(const SquareMatrix& M);
            SquareMatrix& operator*=(const SquareMatrix& M);
            SquareMatrix& operator*=(double n);
            SquareMatrix& transpose();

            friend SquareMatrix operator*(double n, const SquareMatrix& M);
            friend SquareMatrix& operator*=(double n, SquareMatrix& M);
            friend std::istream& operator>>(std::istream& is, SquareMatrix& M);
            friend std::ostream& operator<<(std::ostream& os, const SquareMatrix& M);

            void show_matrix() const;
            double det() const;
            double trace() const;
    };
};

#endif