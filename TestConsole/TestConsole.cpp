#include <iostream>
#include <array>
#include <chrono>
#include <omp.h>

int main() {
    const int size = 100000;
    std::array<int, size> arr;

    // 배열 초기화
    for (int i = 0; i < size; ++i) {
        arr[i] = i + 1;
    }

    // 싱글 스레드 합계 계산 및 시간 측정
    int sum_single = 0;
    auto start_single = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; ++i) {
        sum_single += arr[i];
    }
    auto end_single = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_single = end_single - start_single;

    std::cout << "Single-threaded sum: " << sum_single << "\n";
    std::cout << "Single-threaded duration: " << duration_single.count() << " seconds\n";

    // OpenMP 병렬 합계 계산 및 시간 측정
    int sum_parallel = 0;
    auto start_parallel = std::chrono::high_resolution_clock::now();
#pragma omp parallel for reduction(+:sum_parallel)
    for (int i = 0; i < size; ++i) {
        sum_parallel += arr[i];
    }
    auto end_parallel = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_parallel = end_parallel - start_parallel;

    std::cout << "Parallel sum: " << sum_parallel << "\n";
    std::cout << "Parallel duration: " << duration_parallel.count() << " seconds\n";

    return 0;
}
