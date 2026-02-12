#include "../include/Matrix.h"
#include <random>
#include <stdexcept>

Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    data.resize(r * c);
}

void Matrix::zeroFill() {
    std::fill(data.begin(), data.end(), 0.0);
}

void Matrix::randomFill() {
    std::mt19937 gen(42);
    std::uniform_real_distribution<> dis(1.0, 10.0);

    for (auto &val : data)
        val = dis(gen);
}

Matrix Matrix::multiply(const Matrix& A, const Matrix& B, int numThreads) {

    if (A.cols != B.rows)
        throw std::invalid_argument("Matrix dimensions mismatch");

    Matrix result(A.rows, B.cols);
    result.zeroFill();

    const int BLOCK = 32;  // Cache block size

    auto worker = [&](int startRow, int endRow) {

        for (int ii = startRow; ii < endRow; ii += BLOCK)
            for (int kk = 0; kk < A.cols; kk += BLOCK)
                for (int jj = 0; jj < B.cols; jj += BLOCK)

                    for (int i = ii; i < std::min(ii + BLOCK, endRow); ++i)
                        for (int k = kk; k < std::min(kk + BLOCK, A.cols); ++k) {

                            double temp = A(i, k);

                            for (int j = jj; j < std::min(jj + BLOCK, B.cols); ++j)
                                result(i, j) += temp * B(k, j);
                        }
    };

    std::vector<std::thread> threads;
    int chunk = A.rows / numThreads;
    int start = 0;

    for (int t = 0; t < numThreads; ++t) {
        int end = (t == numThreads - 1) ? A.rows : start + chunk;
        threads.emplace_back(worker, start, end);
        start = end;
    }

    for (auto &th : threads)
        th.join();

    return result;
}
