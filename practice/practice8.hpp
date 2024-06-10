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

    class TextMatrix
    {
        private:
            int row_dim;
            int column_dim;
            std::vector< std::vector<char*> > v2;

            std::string repeat_char(int n, char c);
            std::string col_num_to_str(int n);
        
        public:
            TextMatrix(int row_dim, int column_dim): row_dim(row_dim), column_dim(column_dim), v2(row_dim, std::vector<char*>(column_dim, nullptr)) {}
            TextMatrix(const TextMatrix& T);
            ~TextMatrix();

            friend std::istream& operator>>(std::istream& is, TextMatrix& T);
            friend std::ostream& operator<<(std::ostream& os, TextMatrix& T);

            std::string show_matrix();
    };
};

#endif
