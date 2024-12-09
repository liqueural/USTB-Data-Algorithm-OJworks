// HealthyMealPlan.cpp
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <cstdint> 

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

// 动态规划状态更新函数
void UpdateDP(uint16_t required_nutri, uint16_t food_nutri, int food_idx, std::vector<uint16_t>& dp, std::vector<int>& pre_state) {
    for (int curr_state = required_nutri; curr_state >= 0; curr_state--) {
        if ((curr_state & food_nutri) == food_nutri) { // 如果当前状态curr_state包含food_nutri的所有营养物质
            uint16_t state = curr_state - food_nutri; // 减去curr_state所包含的营养物质
            state &= required_nutri; // 确保state是required_nutri的子集
            if (dp[state] + 1 < dp[curr_state]) { // 更新最小食物数
                dp[curr_state] = dp[state] + 1;
                pre_state[curr_state] = food_idx; // 记录是由食物food_idx产生的状态curr_state
            }
        }
    }
}

int main() {
    int N, M;
    N = readNum(); // 需求的营养物质种类数
    M = readNum(); // 食物种类数

    std::vector<uint8_t> food_nutri(M); // 每种食物含有的营养物质种类数
    for (int i = 0; i < M; i++) {
        food_nutri[i] = readNum(); 
    }

    uint16_t required_nutri = 0; // 目标营养状态
    for (int i = 0; i < N; i++) {
        int curr_idx = readNum();
        required_nutri |= (1 << curr_idx); // 将目标营养状态的相应位置置1
    }

    // 每种食物的营养状态，使用位图表示
    std::vector<uint16_t> foodBinary(M, 0);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < food_nutri[i]; j++) {
            int curr_idx = readNum();
            foodBinary[i] |= (1 << curr_idx); // 将每个食物的营养物质更新到位图中
        }
    }

    std::vector<uint16_t> dp(65536, USHRT_MAX); // dp数组，记录每个状态的最小食物数量
    dp[0] = 0; // 初始化

    std::vector<int> pre_state(65536, -1); 

    for (int i = 0; i < M; i++) {
        UpdateDP(required_nutri, foodBinary[i], i, dp, pre_state); 
    }

    if (dp[required_nutri] == USHRT_MAX) { // 目标状态不可达
        std::cout << "-1" << std::endl;
    }
    else { // 目标状态可达
        // 回溯找到食物路径
        std::vector<int> res;
        for (int s = required_nutri; s != 0; ) {
            int foodIndex = pre_state[s]; // 获取当前状态的食物
            res.push_back(foodIndex); // 存储食物索引
            s -= foodBinary[foodIndex]; // 回到前一个状态
        }

        // 输出结果，按食物编号升序排列
        sort(res.begin(), res.end());
        for (size_t i = 0; i < res.size(); i++) {
            if (i > 0) std::cout << " ";
            std::cout << res[i];
        }
        std::cout << std::endl;
    }

    return 0;
}
