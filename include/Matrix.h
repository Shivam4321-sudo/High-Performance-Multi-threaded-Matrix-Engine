#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <thread>

class Matrix {
public:
    int rows, cols;
    std::vector<double> data;   // Contiguous memory

    Matrix(int r, int c);

    inline double& operator()(int r, int c) {
        return data[r * cols + c];
    }

    inline const double& operator()(int r, int c) const {
        return data[r * cols + c];
    }

    void randomFill();
    void zeroFill();

    static Matrix multiply(const Matrix& A, const Matrix& B, int numThreads);
};

#endif
