#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>


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

        friend SquareMatrix operator*(double n, const SquareMatrix& M);
        friend SquareMatrix& operator*=(double n, SquareMatrix& M);
        friend std::istream& operator>>(std::istream& is, SquareMatrix& M);
        friend std::ostream& operator<<(std::ostream& os, const SquareMatrix& M);

        void show_matrix() const;
        double det() const;
};

SquareMatrix SquareMatrix::operator+(const SquareMatrix& M) const
{
    if (this->dim != M.dim) {
        throw std::invalid_argument("Matrices dimensions do not match.");
    }

    SquareMatrix result(this->dim);
    for (int i = 0; i < this->dim; i++) {
        for (int j = 0; j < this->dim; j++) {
            result.v1[i][j] = this->v1[i][j] + M.v1[i][j];
        }
    }
    return result;
}

SquareMatrix SquareMatrix::operator-(const SquareMatrix& M) const
{
    if (this->dim != M.dim) {
        throw std::invalid_argument("Matrices dimensions do not match.");
    }

    SquareMatrix result(this->dim);
    for (int i = 0; i < this->dim; i++) {
        for (int j = 0; j < this->dim; j++) {
            result.v1[i][j] = this->v1[i][j] - M.v1[i][j];
        }
    }
    return result;
}

SquareMatrix SquareMatrix::operator-() const
{
    return -1 * (*this);
}

SquareMatrix SquareMatrix::operator*(const SquareMatrix& M) const
{
    if (this->dim != M.dim) {
        throw std::invalid_argument("Matrices dimensions do not match.");
    }

    SquareMatrix result(this->dim);
    for (int i = 0; i < this->dim; i++) {
        for (int j = 0; j < this->dim; j++) {
            for (int k = 0; k < this->dim; k++) {
                result.v1[i][j] += this->v1[i][k] * M.v1[k][j];
            } 
        }
    }
    return result;
}

SquareMatrix SquareMatrix::operator*(double n) const
{
    SquareMatrix result(this->dim);
    for (int i = 0; i < this->dim; i++) {
        for (int j = 0; j < this->dim; j++) {
            result.v1[i][j] = n * (this->v1[i][j]);
        }
    }
    return result;
}

SquareMatrix& SquareMatrix::operator+=(const SquareMatrix& M)
{
    if (this->dim != M.dim) {
        throw std::invalid_argument("Matrices dimensions do not match.");
    }

    for (int i = 0; i < this->dim; i++) {
        for (int j = 0; j < this->dim; j++) {
            this->v1[i][j] += M.v1[i][j];
        }
    }
    return *this;
}

SquareMatrix& SquareMatrix::operator-=(const SquareMatrix& M)
{
    if (this->dim != M.dim) {
        throw std::invalid_argument("Matrices dimensions do not match.");
    }

    for (int i = 0; i < this->dim; i++) {
        for (int j = 0; j < this->dim; j++) {
            this->v1[i][j] -= M.v1[i][j];
        }
    }
    return *this;
}

SquareMatrix& SquareMatrix::operator*=(const SquareMatrix& M)
{
    if (this->dim != M.dim) {
        throw std::invalid_argument("Matrices dimensions do not match.");
    }

    for (int i = 0; i < this->dim; i++) {
        for (int j = 0; j < this->dim; j++) {
            for (int k = 0; k < this->dim; k++) {
                this->v1[i][j] *=  M.v1[k][j];
            } 
        }
    }
    return *this;
}

SquareMatrix& SquareMatrix::operator*=(double n)
{
    for (int i = 0; i < this->dim; i++) {
        for (int j = 0; j < this->dim; j++) {
            this->v1[i][j] *= n;
        }
    }
    return *this;
}

SquareMatrix operator*(double n, const SquareMatrix& M)
{
    return M * n;
}

SquareMatrix& operator*=(double n, SquareMatrix& M)
{
    M = M * n;
    return M;
}

std::istream& operator>>(std::istream& is, SquareMatrix& M) 
{
    std::string line;

    for (auto& row : M.v1) {
        if (!std::getline(is, line)) {
            throw std::runtime_error("Failed to read a matrix row.");
        }
        std::istringstream iss(line);
        for (auto& elem : row) {
            if (!(iss >> elem)) {
                throw std::runtime_error("Failed to read matrix elements.");
            }
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const SquareMatrix& M) 
{
    for (const auto& row : M.v1) {
        for (double elem : row) {
            os << elem << " ";
        }
        os << std::endl;
    }
    return os;
}

void SquareMatrix::show_matrix() const
{
    std::cout << "The dimension of this matrix is " << this->dim << "x" << this->dim << '\n';
    for (int i = 0; i < this->dim; i++) {
        for (int j = 0; j < this->dim; j++) {
        std::cout << this->v1[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

double SquareMatrix::det() const
{
    if (this->dim == 1) {
        return this->v1[0][0];
    }
    else if (this->dim == 2) {
        return (this->v1[0][0] * this->v1[1][1]) - (this->v1[0][1] * this->v1[1][0]);
    }
    else {
        double determinant = 0;
        for (int p = 0; p < this->dim; p++) {
            SquareMatrix subMatrix(this->dim - 1);
            for (int i = 1; i < this->dim; i++) {
                int colCount = 0;
                for (int j = 0; j < this->dim; j++) {
                    if (j == p) {
                        continue;
                    }
                    subMatrix.v1[i - 1][colCount] = v1[i][j];
                    colCount++;
                }
            }
            determinant += std::pow(-1, p) * v1[0][p] * subMatrix.det();
        }
        return determinant;
    }
}

int main()
{
    SquareMatrix macOS(3);
    // SquareMatrix iOS(3);
    // SquareMatrix tvOS(3);
    // SquareMatrix visionOS(4);
    // macOS.show_matrix();
    std::cin >> macOS;
    // std::cin >> iOS;
    // std::cin >> visionOS;
    macOS *= 3 ;

    macOS.show_matrix();
    // tvOS.show_matrix(); 
    // visionOS.show_matrix();
    // std::cout << visionOS.det() << std::endl;
    return 0;
}