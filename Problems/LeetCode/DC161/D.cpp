#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int get(ll x) {
    int res = 0;
    while(x != 1) {
        res++;
        x = __builtin_popcountll(x);
    }
    return res;
}
ll dp[64][64][2][2];
class Solution {
public:
    ll popcountDepth(ll n, int k) {
        if(k == 0) return 1;
        if(k == 5) return 0;
        set<int> st;
        for(int i = 1; i <= 64; i++) {
            if(get(i) == k - 1) {
                st.insert(i);
            }
        }
        vector<int> num(64);
        int c = 0;
        while(n) {
            num[++c] = n & 1;
            n >>= 1;
        }
        memset(dp, -1, sizeof(dp));
        auto dfs = [&](this auto &&self, int pos, int cnt, bool lead, bool lim) -> ll {
            if(pos == 0) {
                return st.contains(cnt) ? 1 : 0;
            }
            ll &res = dp[pos][cnt][lead][lim];
            if(res != -1 && !lead && !lim) return res;
            ll cur = 0;
            int up = lim ? num[pos] : 1;
            for(int i = 0; i <= up; i++) {
                if(i == 0 && lead) cur += self(pos - 1, cnt, true, lim && i == up);
                else if(i == 0) cur += self(pos - 1, cnt, false, lim && i == up);
                else cur += self(pos - 1, cnt + 1, false, lim && i == up);
            }
            if(!lead && !lim) res = cur;
            return cur;
        };
        ll ans = dfs(c, 0, true, true);
        if(k == 1) ans--;
        return ans;
    }
};