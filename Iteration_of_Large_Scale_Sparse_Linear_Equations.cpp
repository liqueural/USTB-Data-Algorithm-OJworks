// Iteration_of_Large_Scale_Sparse_Linear_Equations.cpp
#include <iostream>
#include <vector>
#include <tuple>
#include <iomanip>
#include <cmath>
#include <algorithm>

// 比较函数，用于按行优先顺序排序稀疏矩阵的非零元素
bool compare(const std::tuple<int, int, double>& a, const std::tuple<int, int, double>& b) {
    if (std::get<0>(a) == std::get<0>(b)) {
        return std::get<1>(a) < std::get<1>(b);
    }
    return std::get<0>(a) < std::get<0>(b);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    // 读取矩阵大小和非零值个数
    int m, k;
    std::cin >> m >> k;

    // 初始化存储稀疏矩阵的列表
    std::vector<std::tuple<int, int, double>> elements(k);

    // 读取非零元素
    for (int i = 0; i < k; ++i) {
        int row, col;
        double value;
        std::cin >> row >> col >> value;
        elements[i] = std::make_tuple(row, col, value);
    }

    // 按行优先顺序排序稀疏矩阵的非零元素
    std::sort(elements.begin(), elements.end(), compare);

    // 读取向量 b
    std::vector<double> b(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }

    // 初始化解向量 x
    std::vector<double> x(m, 0.0);
    std::vector<double> old_x(m, 0.0);

    // 高斯-赛德尔迭代法求解 Ax = b
    const double tol = 1e-8;
    const int max_iter = 10000;
    bool converged = false;

    for (int iter = 0; iter < max_iter; ++iter) {
        old_x = x;
        for (int i = 0; i < m; ++i) {
            double sum = b[i];
            double diag = 0.0;
            // 使用lower_bound来快速找到当前行的开始位置
            auto start = std::lower_bound(elements.begin(), elements.end(), std::make_tuple(i, 0, 0.0), compare);
            auto end = std::upper_bound(start, elements.end(), std::make_tuple(i, m, 0.0), compare);
            for (auto it = start; it != end; ++it) {
                int row = std::get<0>(*it);
                int col = std::get<1>(*it);
                double value = std::get<2>(*it);
                if (row == i) {
                    if (col == i) {
                        diag = value;
                    }
                    else {
                        sum -= value * x[col];
                    }
                }
            }
            if (fabs(diag) > 1e-12) {
                x[i] = sum / diag;
            }
        }

        // 检查收敛性
        double error = 0.0;
        for (int i = 0; i < m; ++i) {
            error += pow(x[i] - old_x[i], 2);
        }
        if (sqrt(error) < tol) {
            converged = true;
            break;
        }
    }

    // 输出结果
    std::cout << std::fixed << std::setprecision(6);
    if (converged) {
        for (int i = 0; i < m; ++i) {
            std::cout << x[i] << "\n";
        }
    }
    else {
        std::cout << "Solution did not converge" << std::endl;
    }

    return 0;
}
