#include <iostream>
#include <chrono>
#include <cmath>
#include <functional>

// 인라인 최적화가 어렵도록 설계된 복잡한 함수
double ComplexCalculation(double x) {
    double result = 0.0;
    for (int i = 0; i < 100; ++i) {
        if (x > 0) {
            result += std::pow(x, 1.5) - std::log(x + i + 1.0) + std::cos(x + i);
        }
        else {
            result += std::pow(-x, 1.5) + std::log(-x + i + 1.0) - std::sin(x - i);
        }
        result = std::sqrt(result * result + i);
    }
    return result;
}

// 함수 객체 (Functor) 정의
struct ComplexCalculationFunctor {
    double operator()(double x) const {
        double result = 0.0;
        for (int i = 0; i < 100; ++i) {
            if (x > 0) {
                result += std::pow(x, 1.5) - std::log(x + i + 1.0) + std::cos(x + i);
            }
            else {
                result += std::pow(-x, 1.5) + std::log(-x + i + 1.0) - std::sin(x - i);
            }
            result = std::sqrt(result * result + i);
        }
        return result;
    }
};

int main() {
    const int numExecutions = 100000; // 반복 횟수 설정
    double result = 0.0; // 결과 저장용 변수

    // 1. 일반 함수 호출
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= numExecutions; ++i) {
        result += ComplexCalculation(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Direct Function Call: " << duration.count() << " seconds\n";

    // 2. 람다 함수 호출
    auto lambdaFunction = [](double x) {
        double result = 0.0;
        for (int i = 0; i < 100; ++i) {
            if (x > 0) {
                result += std::pow(x, 1.5) - std::log(x + i + 1.0) + std::cos(x + i);
            }
            else {
                result += std::pow(-x, 1.5) + std::log(-x + i + 1.0) - std::sin(x - i);
            }
            result = std::sqrt(result * result + i);
        }
        return result;
        };
    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= numExecutions; ++i) {
        result += lambdaFunction(i);
    }
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Lambda Function: " << duration.count() << " seconds\n";

    // 3. 함수 객체 (Functor) 호출
    ComplexCalculationFunctor functor;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= numExecutions; ++i) {
        result += functor(i);
    }
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Function Object (Functor): " << duration.count() << " seconds\n";

    // 4. 함수 포인터 호출
    double (*functionPointer)(double) = ComplexCalculation;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= numExecutions; ++i) {
        result += functionPointer(i);
    }
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Function Pointer: " << duration.count() << " seconds\n";

    // 5. std::function 호출
    std::function<double(double)> stdFunction = ComplexCalculation;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= numExecutions; ++i) {
        result += stdFunction(i);
    }
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "std::function: " << duration.count() << " seconds\n";

    return 0;
}
