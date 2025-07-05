#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


constexpr ll inf = 1e18;
vector dp(100, vector<vector<vector<ll>>>(100, vector<vector<ll>>(64, vector<ll>(2, -1))));
void solve() { 
    ll x, y;
    cin >> x >> y;
    string s, t;
    while(x) {
        char c = (x & 1) + '0';
        s += c;
        x >>= 1;
    }
    while(y) {
        char c = (y & 1) + '0';
        t += c;
        y >>= 1;
    }
    reverse(s.begin(), s.end());
    reverse(t.begin(), t.end());
    int tot = s.size() + t.size(), len = 0;
    for(int i = 0; i < s.size() && i < t.size(); i++) {
        if(s[i] == t[i]) {
            tot -= 2;
            len += 1;
        } else {
            break;
        }
    }
    int a = s.size() - len, b = t.size() - len;
    auto dfs = [&](this auto &&dfs, int x, int y, int cur, int ok) -> ll {
        if(x == 0 && y == 0) {
            return 0;
        }
        if(cur > 62) {
            return inf;
        }
        ll &res = dp[x][y][cur][ok];
        if(res != -1) return res;
        res = dfs(x, y, cur + 1, ok);
        ll t = inf;
        if(!ok) {
            if(x >= cur) t = dfs(x - cur, y, cur + 1, ok);
            if(t < inf) res = min(res, t + (1LL << cur));
            t = inf;
            if(y >= cur) t = dfs(x, y - cur, cur + 1, ok);
            if(t < inf) res = min(res, t + (1LL << cur));
        } else {
            if(x) t = dfs(max(0, x - cur), y, cur + 1, ok);
            if(t < inf) res = min(res, t + (1LL << cur));
            t = inf;
            if(y) t = dfs(x, max(0, y - cur), cur + 1, ok);
            if(t < inf) res = min(res, t + (1LL << cur));
        }
        return res;
    };
    ll ans = inf;
    while(a <= s.size() || b <= t.size()) {
        if(a < s.size() || b < t.size()) {
            ans = min(ans, dfs(a, b, 1, 0));
        } else {
            ans = min(ans, dfs(a, b, 1, 1));
        }
        a++;
        b++;
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
