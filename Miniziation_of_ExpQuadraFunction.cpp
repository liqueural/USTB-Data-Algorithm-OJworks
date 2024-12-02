// Miniziation_of_ExpQuadraFunction.cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <stdexcept>

const double EPSILON = 1e-8;
const double ALPHA = 0.1;  // 步长因子

// 计算二次项 1/2 * x^T * A * x
double quadratic_term(const std::vector<std::vector<double>>& A, const std::vector<double>& x) {
    double quadr_term = 0.0;
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < A.size(); ++j) {
            quadr_term += x[i] * A[i][j] * x[j];
        }
    }
    return 0.5 * quadr_term;
}

// 计算函数 g(x) = exp(1/2 * x^T * A * x) * A * x - b
std::vector<double> g(const std::vector<std::vector<double>>& A, const std::vector<double>& b, const std::vector<double>& x) {
    double exp_term = exp(quadratic_term(A, x));
    std::vector<double> result(A.size(), 0.0);
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < A.size(); ++j) {
            result[i] += A[i][j] * x[j];
        }
        result[i] = exp_term * result[i] - b[i];
    }
    return result;
}

// 计算 Hessian 矩阵的对角线元素
std::vector<double> hessian_diagonal(const std::vector<std::vector<double>>& A, const std::vector<double>& x) {
    double quadr_term = quadratic_term(A, x);
    double exp_term = exp(quadr_term);
    std::vector<double> result(A.size(), 0.0);
    for (size_t i = 0; i < A.size(); ++i) {
        result[i] = exp_term * (A[i][i] + quadr_term);
    }
    return result;
}

// 牛顿法迭代求解
std::vector<double> newton_method(const std::vector<std::vector<double>>& A, const std::vector<double>& b, size_t N) {
    std::vector<double> x(N, 0.0);
    for (int iter = 0; iter < 1000; ++iter) {
        std::vector<double> grad = g(A, b, x);
        std::vector<double> hessian_diag = hessian_diagonal(A, x);

        std::vector<double> delta_x(N, 0.0);
        for (size_t i = 0; i < N; ++i) {
            if (std::abs(hessian_diag[i]) < EPSILON) {
                throw std::runtime_error("Hessian diagonal element too small, potential division by zero.");
            }
            delta_x[i] = -grad[i] / hessian_diag[i];
        }

        for (size_t i = 0; i < N; ++i) {
            x[i] += ALPHA * delta_x[i];
        }

        double norm = 0.0;
        for (size_t i = 0; i < N; ++i) {
            norm += grad[i] * grad[i];
        }
        if (sqrt(norm) < EPSILON) {
            break;
        }
    }
    return x;
}

// 计算目标函数 f(x)
double f(const std::vector<std::vector<double>>& A, const std::vector<double>& b, const std::vector<double>& x) {
    double quadr_term = quadratic_term(A, x);
    double linear_term = 0.0;
    for (size_t i = 0; i < A.size(); ++i) {
        linear_term += b[i] * x[i];
    }
    return exp(quadr_term) - linear_term;
}

int main() {
    size_t N;
    std::cin >> N;

    std::vector<std::vector<double>> A(N, std::vector<double>(N));
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            std::cin >> A[i][j];
        }
    }

    std::vector<double> b(N);
    for (size_t i = 0; i < N; ++i) {
        std::cin >> b[i];
    }

    try {
        std::vector<double> x = newton_method(A, b, N);
        double min_value = f(A, b, x);
        std::cout << std::fixed << std::setprecision(4) << min_value << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
