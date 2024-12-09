// MissingChopsticks.cpp
#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <unordered_map>

int main() {
	int N;	
	// scanf("%d", &N);
	std::cin >> N;

	// 创建一个哈希表，用于存放所有的未丢失筷子长度
	std::unordered_map<int, int> cpsticks;
	for (int i = 0; i < 2 * N - 2; i++) {
		int length;
		// scanf("%d", length);
		std::cin >> length;
		cpsticks[length]++;
	}

	// 创建一个数组，用于存放丢失的筷子
	std::vector<int> missingcpsticks;
	// 对未丢失筷子的长度进行配对，配对结果为奇数的筷子一定是丢失的
	for (const auto pair : cpsticks) {
		if (pair.second % 2 != 0) {
			missingcpsticks.push_back(pair.first);
		}
	}

	// 对丢失筷子进行排序
	std::sort(missingcpsticks.begin(), missingcpsticks.end());
	printf("%d\n%d\n", missingcpsticks[0], missingcpsticks[1]);

	return 0;
}
