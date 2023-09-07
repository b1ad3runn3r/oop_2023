#include "matrix.h"

#include <algorithm>
#include <iterator>
#include <vector>

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

        for (const auto &row: matrix.rows) {
            if (row.empty()) {
                for (int i = 0; i < matrix.n; i++) {
                    std::cout << "0 ";
                }
            }

            int idx = 0;
            for (int i = 0; i < matrix.n; ++i) {
                if (row[idx].column == i) {
                    std::cout << row[idx].data << ' ';
                    ++idx;
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
            for (auto src_row : source.rows) {
                if (src_row.empty()) {
                    --res.m;
                    continue;
                }

                unsigned int idx_greater = 0;
                unsigned int idx_lower = 0;
                auto src_row_size = src_row.size();

                for (; idx_greater < src_row_size; ++idx_greater) {
                    if (src_row[idx_greater].data > 0) {
                        break;
                    }
                }

                for (; idx_lower < src_row_size; ++idx_lower) {
                    if (src_row[idx_lower].data < 0) {
                        break;
                    }
                }

                if (idx_greater == src_row_size && idx_lower == src_row_size) {
                    --res.m;
                    continue;
                }

                if (idx_greater > idx_lower) {
                    std::swap(idx_greater, idx_lower);
                }
                else if (idx_greater == src_row_size) {
                    idx_greater = 0;
                }
                else if(idx_lower == src_row_size) {
                    idx_lower = src_row_size - 1;
                }

                std::vector<NonZeroElem> res_row;
                res_row.reserve(idx_lower - idx_greater + 1);
                std::copy(src_row.begin() + idx_greater,
                          src_row.begin() + idx_lower + 1,
                          std::back_inserter(res_row)
                          );

                res.rows.push_back(res_row);
            }
        }
        catch (...) {
            erase(res);
            throw ;
        }

        return res;
    }
}
