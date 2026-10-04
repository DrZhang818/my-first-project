#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
i64 multiKnapsack(int n, int capacity, const vector<int>& w, const vector<i64>& v,
                  const vector<int>& m) {
    vector<vector<i64>> dp(2, vector<i64>(capacity + 1, 0));
    for(int i = 1; i <= n; i++) {
        auto& pre = dp[(i - 1) % 2];
        auto& cur = dp[i % 2];
        for(int rem = 0; rem < w[i]; rem++) {
            deque<int> q;
            for(int j = rem; j <= capacity; j += w[i]) {
                while(!q.empty() &&
                      pre[j] >= pre[q.back()] + (j - q.back()) / w[i] * v[i]) {
                    q.pop_back();
                }
                q.push_back(j);
                while(!q.empty() && q.front() < (j - 1LL * m[i] * w[i])) {
                    q.pop_front();
                }
                cur[j] = max(pre[j], pre[q.front()] + (j - q.front()) / w[i] * v[i]);
            }
        }
    }
    return dp[n % 2][capacity];
}
