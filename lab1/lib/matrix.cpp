#include "matrix.h"

#include <list>
#include <algorithm>

namespace Lab1 {
    SparseMatrix input() {
        SparseMatrix matrix;
        try {
            std::cout << "Enter number of rows: ";
            matrix.m = getNum<int>(0);

            std::cout << "Enter number of columns: ";
            matrix.n = getNum<int>(0);

            std::cout << "Now enter matrix elements: " << std::endl;

            for (int i = 0; i < matrix.m; ++i) {
                std::vector<NonZeroElem> row;
                for (int j = 0; j < matrix.n; ++j) {
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

    void output(const std::string &msg, const SparseMatrix &matrix) {
        std::cout << msg << std::endl;

        for (auto row: matrix.rows) {
            auto row_iter = row.begin();
            for (int i = 0; i < matrix.n; ++i) {
                if (row.empty()) {
                    std::cout << "0 ";
                    continue;
                }

                if (row_iter->column == i) {
                    std::cout << row_iter->data << ' ';
                    ++row_iter;
                }
                else {
                    std::cout << "0 ";
                }
            }

            std::cout << std::endl;
        }
    }

    void erase(SparseMatrix &matrix) {
        for (auto row : matrix.rows) {
            row.clear();
        }

        matrix.rows.clear();
        matrix.m = 0;
        matrix.n = 0;
    }

    SparseMatrix proceed(const SparseMatrix &source) {
        SparseMatrix res;
        res.m = source.m;
        res.n = source.n;

        try {
            for (auto row : source.rows) {
                if (row.empty()) {
                    --res.m;
                    continue;
                }
                auto iter_greater = row.begin();
                auto iter_lower = iter_greater;

                while (iter_greater != row.end()) {
                    if (iter_greater->data > 0) {
                        break;
                    }

                    ++iter_greater;
                }

                while (iter_lower != row.end()) {
                    if (iter_lower->data < 0) {
                        break;
                    }

                    ++iter_lower;
                }

                if (std::distance(iter_greater, iter_lower) < 0) {
                    --res.m;
                    continue;
                }

                std::vector<NonZeroElem> tmp;
                if (iter_greater != row.end() && iter_lower != row.end()) {
                    ++iter_greater;
                    std::copy(iter_greater, iter_lower, std::back_inserter(tmp));
                }
                else {
                    std::copy(row.begin(), row.end(), std::back_inserter(tmp));
                }

                res.rows.push_back(tmp);
            }
        }
        catch (...) {
            erase(res);
            throw ;
        }

        return res;
    }
}
