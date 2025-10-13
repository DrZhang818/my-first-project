#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

ll dp[18][2][2][2];
int num[18];
int cnt = 0;

ll dfs(int pos, int tag, int leada, int leadb) {
    if(pos == 0) {
        return tag == 1 ? 0 : 1;
    }

    if(dp[pos][tag][leada][leadb] != -1) {
        return dp[pos][tag][leada][leadb];
    }

    int cur = (num[pos] - tag + 10) % 10;
    int nxt = 0;
    if(num[pos] < tag) {
        nxt = 1;
    }

    ll res = 0;

    int L = 0, R = leada ? 0 : 9;
    if(leadb) {
        L = max(L, cur);
        R = min(R, cur);
    }

    for(int i = L; i <= R; i++) {
        nxt |= (i > cur);

        if(pos == cnt && (i == 0 || i == cur)) {
            continue;
        }

        if(i == cur) {
            res += dfs(pos - 1, nxt, i == 0, true);
        } else {
            res += dfs(pos - 1, nxt, i == 0, false);
        }
    }
    return dp[pos][tag][leada][leadb] = res;
}

ll work(ll n) {
    cnt = 0;
    while(n) {
        num[++cnt] = n % 10;
        n /= 10;
    }
    for(int i = 1; i <= cnt / 2; i++) {
        swap(num[i], num[cnt - i + 1]);
    } 
    return dfs(cnt, 0, 0, 0);
}


class Solution {
public:
    ll countNoZeroPairs(ll n) {
        memset(dp, -1, sizeof(dp));
        ll ans = work(n);
        return ans;
    }
};