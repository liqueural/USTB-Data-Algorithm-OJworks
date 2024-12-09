// FindMedian.cpp
#include <iostream>
#include <vector>
#include <queue>

int readNum() {
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    int v = 0;
    while (ch >= '0' && ch <= '9') {
        v = v * 10 + ch - '0';
        ch = getchar();
    }
    return v;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    n = readNum();
    m = readNum();

    std::vector<int> T(n);
    for (int i = 0; i < n; ++i) {
        T[i] = readNum();
    }

    std::vector<double> medians(n + 1); // 存储从 T[0] 到 T[i] 的中位数
    std::priority_queue<int> maxHeap; // 大根堆，存放较小的一半
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap; // 小根堆，存放较大的一半

    for (int i = 0; i < n; ++i) {
        if (maxHeap.empty() || T[i] <= maxHeap.top()) {
            maxHeap.push(T[i]);
        }
        else {
            minHeap.push(T[i]);
        }

        // 平衡两个堆
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }

        // 计算中位数
        if (maxHeap.size() == minHeap.size()) {
            medians[i + 1] = (maxHeap.top() + minHeap.top()) / 2.0;
        }
        else {
            medians[i + 1] = maxHeap.top();
        }
    }

    // 查询处理
    for (int i = 0; i < m; ++i) {
        int b = readNum();
        std::cout << medians[b + 1] << std::endl;
    }

    return 0;
}
