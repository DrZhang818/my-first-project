#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int num[17];
ll dp[17][10][3][17];

auto init = []() -> int {
    memset(dp, -1, sizeof(dp));
    return 1;
} ();

ll dfs(int pos, int las, int state, int cnt, bool lim) {
    if(pos == 0) {
        return cnt;
    }
    if(las != -1 && !lim && dp[pos][las][state][cnt] != -1) {
        return dp[pos][las][state][cnt];
    }
    int up = lim ? num[pos] : 9;
    ll res = 0;
    for(int i = 0; i <= up; i++) {
        if(las == -1) {
            if(i == 0) {
                res += dfs(pos - 1, -1, 2, cnt, lim && i == up);
            } else {
                res += dfs(pos - 1, i, 2, cnt, lim && i == up);
            }
        } else {
            int s = i > las ? 1 : (i < las ? 0 : 2);
            res += dfs(pos - 1, i, s, cnt + ((state ^ s) == 1), lim && i == up);
        }
    }
    if(las != -1 && !lim) {
        dp[pos][las][state][cnt] = res;
    }
    return res;
}

ll cal(ll x) {
    int cnt = 0;
    while(x) {
        num[++cnt] = x % 10;
        x /= 10;
    }
    return dfs(cnt, -1, 2, 0, true);
}

class Solution {
public:
    ll totalWaviness(ll num1, ll num2) {
        return cal(num2) - cal(num1 - 1);
    }
};