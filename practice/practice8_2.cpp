#include "practice8.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>


namespace MATRIX
{
    TextMatrix::TextMatrix(const TextMatrix& T) : row_dim(T.row_dim), column_dim(T.column_dim), v2(row_dim, std::vector<char*>(column_dim, nullptr)) 
    {
        for (int i = 0; i < row_dim; i++) {
            for (int j = 0; j < column_dim; j++) {
                v2[i][j] = new char[std::strlen(T.v2[i][j]) + 1];
                std::strcpy(v2[i][j], T.v2[i][j]);
            }
        }
    }

    TextMatrix::~TextMatrix()
    {
        for (int i = 0; i < this->row_dim; i++) {
            for (int j = 0; j < this->column_dim; j++) {
                delete [] this->v2[i][j];
            }
        }
    }

    std::istream& operator>>(std::istream& is, TextMatrix& T)
    {
        char temp[1024];
        for (int i = 0; i < T.row_dim; i++) {
            for (int j = 0; j < T.column_dim; j++) {
                is >> temp;
                T.v2[i][j] = new char[std::strlen(temp) + 1];
                std::strcpy(T.v2[i][j], temp);
            }
        }
        return is;
    }

    std::ostream& operator<<(std::ostream& os, TextMatrix& T)
    {
        os << T.show_matrix();
        return os;
    }

    std::string TextMatrix::show_matrix() 
    {
        std::string total_table;
        std::vector<int> columnWidths(this->column_dim, 0);
        for (int i = 0; i < this->row_dim; i++) {
            for (int j = 0; j < this->column_dim; j++) {
                int length = std::strlen(this->v2[i][j]);
                if (length > columnWidths[j]) {
                    columnWidths[j] = length;
                }
            }
        }

        total_table += "    ";
        int total_wide = 4;
        for (int i = 0; i < this->column_dim; i++) {
            if (columnWidths[i]) {
                int max_len = std::max(2, columnWidths[i]);
                total_table += " | " + col_num_to_str(i);
                total_table += repeat_char(max_len - col_num_to_str(i).length(), ' ');
                total_wide += (max_len + 3);
            }
        }
        total_table += "\n";

        for (int i = 0; i < this->row_dim; i++) {
            total_table += repeat_char(total_wide, '-');
            total_table += "\n" + std::to_string(i + 1);
            total_table += repeat_char(4 - std::to_string(i + 1).length(), ' ');
            for (int j = 0; j < this->column_dim; j++) {
                if (columnWidths[j]) {
                    int max_len = std::max(2, columnWidths[j]);
                    std::string s = "";
                    if (this->v2[i][j]) {
                        s = this->v2[i][j];
                    }
                    total_table += " | " + s;
                    total_table += repeat_char(max_len - s.length(), ' ');
                }
            }
            total_table += "\n";
        }
        return total_table;
    }

    std::string TextMatrix::repeat_char(int n, char c) {
        std::string s = "";
        for (int i = 0; i < n; i++) 
            s.push_back(c);
        return s;
    }

    std::string TextMatrix::col_num_to_str(int n) {
        std::string s = "";
        if (n < 26) {
            s.push_back('A' + n);
        } else {
            char first = 'A' + n / 26 - 1;
            char second = 'A' + n % 26;
            s.push_back(first);
            s.push_back(second);
        }
        return s;
    }
};
