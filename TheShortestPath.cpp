// TheShortestPath.cpp
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int MAXN = 100000;
const int MAXM = 200000;

struct Edge {
    int to, weight;
};

vector<Edge> graph[MAXN + 1];  //邻接表
int d[MAXN + 1];  

// 快速读入
int readNum() {
    char ch = getchar();
    while (ch < '0' or ch > '9') ch = getchar();
    int v = 0;
    while (ch >= '0' and ch <= '9') {
        v = v * 10 + ch - '0';
        ch = getchar();
    }
    return v;
}

void fast_algorithm(int src, int n) {
    fill(d, d + n + 1, INT_MAX);
    d[src] = 0;
    queue<int> q;
    q.push(src);
    vector<bool> inQueue(n + 1, false);
    inQueue[src] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inQueue[u] = false;
        for (const Edge& e : graph[u]) {
            int v = e.to, w = e.weight;
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
                if (!inQueue[v]) {
                    q.push(v);
                    inQueue[v] = true;
                }
            }
        }
    }
}

int main() {
    int n = readNum(), m = readNum(), q = readNum();

    for (int i = 0; i < m; ++i) {
        int u = readNum(), v = readNum(), w = readNum();
        graph[u].push_back({ v, w });
        graph[v].push_back({ u, w });
    }
    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; ++i) {
        int src = readNum(), end = readNum();
        queries[i] = { src, end };
    }

    for (int i = 0; i < q; ++i) {
        int src = queries[i].first;
        fast_algorithm(src, n);

        int end = queries[i].second;
        cout << d[end] << endl;
    }

    return 0;
}
