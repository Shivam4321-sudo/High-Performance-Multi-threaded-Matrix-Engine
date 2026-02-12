#include "../include/Matrix.h"
#include <iostream>
#include <chrono>

int main() {

    int size = 1000;
    int threads = std::thread::hardware_concurrency();

    std::cout << "Matrix Size: " << size << "x" << size << "\n";
    std::cout << "Using Threads: " << threads << "\n";

    Matrix A(size, size);
    Matrix B(size, size);

    A.randomFill();
    B.randomFill();

    auto start = std::chrono::high_resolution_clock::now();

    Matrix C = Matrix::multiply(A, B, threads);

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    std::cout << "Optimized Multiplication Time: "
              << duration.count() << " seconds\n";

    return 0;
}
