// Library.cpp
#include <iostream> 
#include <unordered_map> 
#include <vector> 
#include <sstream> 
#include <string> 
// using namespace std;

// 图书馆的书
std::vector<bool> books(1000 * 1000);    
// 最终输出的结果，用vector<bool>类型存储
bool result[1000 * 1000] = { false };
int main()
{
    // 读入图书馆的书，以字符串形式读入，可以减少时间限制
    unsigned int n;
    std::string input;
    getline(std::cin, input);
    std::stringstream ss(input);
    while (ss >> n)
    {
        books[n] = true;
    }
    int m;  // 操作的次数
    std::cin >> m;
    // scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        int opt;    // 操作编码
        unsigned int wanted_id;  // 待操作的书籍编号
        // scanf("%d%u", &opt, &wanted_id);
        std::cin >> opt >> wanted_id;
        if (opt == 1)
        {
            if (books[wanted_id] == true) { result[i] = (true); }
            else {
                result[i] = (false); 
            } continue;
        }
        if (opt == 2)
        {
            if (books[wanted_id] == true)
            {
                books[wanted_id] = false;
                result[i] = (true);
            }
            else
            {
                result[i] = (false);
            }
            continue;
        }
        if (opt == 3)
        {
            if (books[wanted_id] == false)
            {
                books[wanted_id] = true;
                result[i] = (true);
            }
            else
            {
                result[i] = (false);
            }
            continue;
        }
    }
    for (int i = 0; i < m; i++) { std::cout << result[i]; }
}
