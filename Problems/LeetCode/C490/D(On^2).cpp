#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

template <typename T>
auto get(T& x) {
    int c2 = 0, c3 = 0, c5 = 0;
    while(x % 2 == 0) { c2++; x /= 2; }
    while(x % 3 == 0) { c3++; x /= 3; }
    while(x % 5 == 0) { c5++; x /= 5; }
    return tuple(c2, c3, c5);
};

constexpr int offset = 38;
array<array<i64, 80>, 20> dp {};

auto init = []() -> int {
    dp[0][offset] = 1;
    for(int i = 1; i < 20; i++) {
        for(int j = 1; j < 80; j++) {
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j] + dp[i - 1][j + 1];
        }
    }
    return 1;
}();

auto calc(int x, int y) -> i64 {
    return dp[x][y + offset];
};

class Solution {
public:
    int countSequences(vector<int>& a, i64 k) {
        int n = a.size();
        auto [t2, t3, t5] = get(k);
        if(k != 1) return 0;

        array<int, 10> cnt {};
        for(int x : a) {
            cnt[x]++;
        }

        int ans = 0;
        int ways_1 = 1;
        for(int i = 0; i < cnt[1]; i++) {
            ways_1 *= 3;
        }
        int ways_5 = calc(cnt[5], t5);

        for(int d6 = -cnt[6]; d6 <= cnt[6]; d6++) {
            for(int d4 = -cnt[4]; d4 <= cnt[4]; d4++) {

                int d3 = t3 - d6;
                int d2 = t2 - 2 * d4 - d6;

                ans += calc(cnt[2], d2) * calc(cnt[3], d3) * calc(cnt[4], d4) * calc(cnt[6], d6);
            }
        }

        return ans * ways_1 * ways_5;
    }
};