#include "matrix.h"

#include <list>

namespace Lab1 {
    SparseMatrix input() {
        SparseMatrix matrix;
        try {
            std::cout << "Enter number of rows: ";
            matrix.m = getNum<unsigned int>();

            std::cout << "Enter number of columns: ";
            matrix.n = getNum<unsigned int>();

            for (unsigned int i = 0; i < matrix.m; ++i) {
                std::list<NonZeroElem> row;
                for (unsigned int j = 0; j < matrix.n; ++j) {
                    int num = getNum<int>();
                    if (num == 0) {
                        continue;
                    }
                    else {
                        row.push_back({j, num});
                    }
                }

                matrix.rows.push_back(row);
            }
        }
        catch (...) {
            erase(matrix);
            throw ;
        }

        return matrix;
    }

    void output(const std::string &msg, SparseMatrix &matrix) {
        //TODO: make output to not erase whole matrix
        std::cout << msg << std::endl;

        for (unsigned int i = 0; i < matrix.m; ++i) {
            std::list<NonZeroElem> row = matrix.rows.front();
            for (unsigned int j = 0; j < matrix.n; ++j) {
                if (row.empty()) {
                    std::cout << 0 << ' ';
                    continue;
                }
                NonZeroElem cur = row.front();

                if (cur.column == j) {
                    std::cout << cur.data << ' ';
                    row.pop_front();
                }
                else {
                    std::cout << 0 << ' ';
                }
            }

            std::cout << std::endl;
            matrix.rows.pop_front();
        }
    }

    void erase(SparseMatrix &matrix) {
        matrix.m = 0;
        matrix.n = 0;
    }
}
