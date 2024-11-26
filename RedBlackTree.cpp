// RedBlackTree.cpp
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <unordered_set>

std::set<unsigned int> segments;

std::vector<unsigned int> find(const std::vector<unsigned int>& queries) {
    std::vector<unsigned int> results;
    for (unsigned int query : queries) {
        if (query <= *segments.begin()) {  // 如果查询的值小于等于第一个划分点，则返回1
            results.push_back(1);
        }
        else {
            auto it = segments.upper_bound(query);
            if (it != segments.begin()) {
                --it;  // 回退到不大于查询值的最大元素
            }
            results.push_back(*it);  // 添加找到的划分起点
        }
    }
    return results;
}

void split(const std::vector<unsigned int>& splits) {     //分割
    for (unsigned int split : splits) {
        segments.insert(split);
    }
}

//void merge(const std::vector<int>& merges) {     //合并
//    std::set<int> delete_segments;
//    for (int merge : merges) {
//        auto it = segments.upper_bound(merge);
//        if (it != segments.end()) {
//            delete_segments.insert(*it);
//        }
//        segments.erase(merge);
//    }
//    for (int segment : delete_segments) {
//        segments.erase(segment);
//    }
//}

//void merge(const std::vector<int>& merges) {
//    std::set<int> to_delete;
//    for (int merge : merges) {
//        auto it = segments.upper_bound(merge);
//        if (it != segments.end() && *it == merge) {
//            // 如果合并点本身是一个划分点，则跳过
//            continue;
//        }
//        if (it != segments.begin()) {
//            --it;
//        }
//        to_delete.insert(*it);
//    }
//    for (int segment : to_delete) {
//        segments.erase(segments.find(segment));
//    }
//}

//void merge(const std::vector<int>& merges) {
//    std::set<int> to_delete;
//    for (int merge : merges) {
//        auto it = segments.lower_bound(merge);
//        if (it != segments.end() && *it == merge) {
//            // 如果合并点本身是一个划分点，则跳过
//            continue;
//        }
//        if (it != segments.begin()) {
//            --it;
//            if (it != segments.end()) {
//                auto next_it = std::next(it);
//                if (next_it != segments.end()) {
//                    to_delete.insert(*next_it);
//                }
//            }
//        }
//        else if (it != segments.end()) {
//            to_delete.insert(*it);
//        }
//    }
//    // 删除重复的划分点
//    for (int segment : to_delete) {
//        segments.erase(segment);
//    }
//}

//void merge(std::set<unsigned int> &s, std::vector<unsigned int> &elem) {
//    std::set<unsigned int> to_delete;
//    for (unsigned int e : elem) {
//        if (next(s.find(e)) != s.end()) {
//            to_delete.insert(*next(s.find(e)));
//        }
//        else if (s.upper_bound(e) != s.end()) {
//            to_delete.insert(*s.upper_bound(e));
//        }
//    }
//    for (unsigned int i : to_delete) {
//        s.erase(i);
//    }
//}

//void merge(std::set<unsigned int>& s, const std::vector<unsigned int>& elem) {
//    std::set<unsigned int> to_delete;
//    for (unsigned int e : elem) {
//        auto it = s.find(e);
//        if (it != s.end()) {
//            //continue;  // 如果合并点本身是一个划分点，则跳过
//            to_delete.insert(e);
//        }
//        auto next_it = s.upper_bound(e);
//        if (next_it != s.end()) {
//            to_delete.insert(*next_it);
//        }
//    }
//    for (unsigned int i : to_delete) {
//        s.erase(i);
//    }
//}

void merge(std::set<unsigned int>& s, const std::vector<unsigned int>& elem) {
    std::unordered_set<unsigned int> to_del;
    for (unsigned int e : elem) {
        auto it = s.lower_bound(e + 1);
        if (it != s.end()) {
            to_del.insert(*it);
        }
    }
    for (unsigned int i : to_del) {
        s.erase(i);
    }
}

void print() {      //打印
    for (auto it = segments.begin(); it != segments.end(); ++it) {
        if (it != segments.begin()) {
            std::cout << " ";
        }
        std::cout << *it;
    }
    std::cout << std::endl;
}

int main() {
    unsigned int n, m;
    std::cin >> n >> m;

    std::vector<unsigned int> initial(n);
    for (unsigned int i = 0; i < n; i++) {
        std::cin >> initial[i];
        segments.insert(initial[i]);
    }

    for (unsigned int i = 0; i < m; ++i) {
        unsigned int op;
        std::cin >> op;
        if (op == 0) {
            unsigned int q;
            std::cin >> q;
            std::vector<unsigned int> queries(q);
            for (unsigned int i = 0; i < q; i++) {
                std::cin >> queries[i];
            }
            std::vector<unsigned int> results = find(queries);
            for (unsigned int res : results) {
                std::cout << res << " ";
            }
            std::cout << std::endl;
            /*int q;
            std::cin >> q;
            std::vector<int> queries(q);
            for (int i = 0; i < q; i++) {
                std::cin >> queries[i];
            }
            find(queries);*/
        } 
        else if (op == 1) {
            unsigned int q;
            std::cin >> q;
            std::vector<unsigned int> splits(q);
            for (unsigned int i = 0; i < q; i++) {
                std::cin >> splits[i];
            }
            split(splits);
        }
        else if (op == 2) {
            unsigned int q;
            std::cin >> q;
            std::vector<unsigned int> merges(q);
            for (unsigned int i = 0; i < q; i++) {
                std::cin >> merges[i];
            }
            merge(segments, merges);
        }
        else if (op == 3) {
            print();
        }
    }
    return 0;
}
