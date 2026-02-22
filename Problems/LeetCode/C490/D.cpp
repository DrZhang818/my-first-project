#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

template <typename T>
auto get(T& x) -> tuple<int,int,int> {
    int c2 = 0, c3 = 0, c5 = 0;
    while(x % 2 == 0) {
        x /= 2;
        c2++;
    }
    while(x % 3 == 0) {
        x /= 3;
        c3++;
    }
    while(x % 5 == 0) {
        x /= 5;
        c5++;
    }
    return tuple(c2, c3, c5);
};

class Solution {
public:
    int countSequences(vector<int>& a, i64 k) {
        int n = a.size();

        int max_2 = 0, max_3 = 0, max_5 = 0;
        vector<array<int, 3>> fac(n);

        for(int i = 0; i < n; i++) {
            auto [x, y, z] = get(a[i]);
            tie(fac[i][0], fac[i][1], fac[i][2]) = tuple(x, y, z);
            max_2 += x;
            max_3 += y;
            max_5 += z;
        }

        auto [c2, c3, c5] = get(k);

        if(k != 1 || c2 > max_2 || c3 > max_3 || c5 > max_5) {
            return 0;
        }

        int dim2 = max_2 << 1 | 1;
        int dim3 = max_3 << 1 | 1;
        int dim5 = max_5 << 1 | 1;
        int dim35 = dim3 * dim5;
        int siz = dim2 * dim3 * dim5;

        vector<int> dp(siz);

        auto getId = [&](int x, int y, int z) -> int {
            return (x + max_2) * dim35 + (y + max_3) * dim5 + (z + max_5);
        };
        dp[getId(0, 0, 0)] = 1;

        for(int i = 0; i < n; i++) {
            auto ndp = dp;
            int d = fac[i][0] * dim35 + fac[i][1] * dim5 + fac[i][2];

            for(int i = 0; i < siz; i++) {
                if(dp[i] > 0) {
                    ndp[i + d] += dp[i];
                    ndp[i - d] += dp[i];
                }
            }

            dp = move(ndp);
        }

        return dp[getId(c2, c3, c5)];
    }
};