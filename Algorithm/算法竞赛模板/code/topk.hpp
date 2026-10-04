#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
// 不同 key 的前 K 大值；空槽 key = -1、val = -INF（key 可能为 -1 时需改哨兵）
template <int K> struct TopK {
    static constexpr i64 INF = numeric_limits<i64>::max() / 4;
    struct Node {
        i64 val = -INF;
        int key = -1;
    };
    array<Node, K> a;
    void norm() {
        sort(a.begin(), a.end(),
             [](const Node& x, const Node& y) { return x.val > y.val; });
    }
    // 插入 (key, val)：同 key 保留较大值；否则尝试替换第 K 小
    void add(int key, i64 val) {
        for(auto& x : a) {
            if(x.key == key) {
                x.val = max(x.val, val);
                norm();
                return;
            }
        }
        if(val > a[K - 1].val) {
            a[K - 1] = {val, key};
            norm();
        }
    }
    // 返回未被禁用 key 的最大 val；无候选时返回 -INF
    i64 get(int ban1 = -1, int ban2 = -1) const {
        for(const auto& x : a) {
            if(x.key != ban1 && x.key != ban2) {
                return x.val;
            }
        }
        return -INF;
    }
};
