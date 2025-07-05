#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<long,long> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, q;
    cin >> n >> q;
    auto dfs1 = [&](this auto&& dfs, ll x, ll y) -> ll {
        int tx = (x == 0 ? 0 : __lg(x)) + 1, ty = (y == 0 ? 0 : __lg(y)) + 1;
        int k = max(tx, ty);
        if(k == 1) {
            if(x == 0 && y == 0) return 1;
            else if(x == 0 && y == 1) return 4;
            else if(x == 1 && y == 0) return 3;
            else return 2;
        }
        ll len = (1LL << k - 1);
        int flag1 = x / len, flag2 = y / len;
        if(flag1 == 0 && flag2 == 1) return 3 * (1LL << 2 * (k - 1)) + dfs(x, y - len);
        else if(flag1 == 1 && flag2 == 0) return 2 * (1LL << 2 * (k - 1)) + dfs(x - len, y);
        else return (1LL << (2 * (k - 1))) + dfs(x - len, y - len);    
    };
    auto dfs2 = [&](this auto &&dfs2, ll d) -> PII {
        ll k = 1;
        while((1LL << 2 * k) < d) k++;
        if(k == 1) {
            if(d == 1) return {1, 1};
            if(d == 2) return {2, 2};
            if(d == 3) return {2, 1};
            if(d == 4) return {1, 2};
        }
        ll pk = (1LL << 2 * (k - 1));
        if(d <= 2 * pk) {
            PII res = dfs2(d - pk);
            return {res.first + (1LL << k - 1), res.second + (1LL << k - 1)};
        } else if(d <= 3 * pk) {
            PII res = dfs2(d - 2 * pk);
            return {res.first + (1LL << k - 1), res.second};
        } else {
            PII res = dfs2(d - 3 * pk);
            return {res.first, res.second + (1LL << k - 1)};
        }
    };
    while(q--) {
        string s;
        cin >> s;
        if(s == "->") {
            ll x, y;
            cin >> x >> y;
            x--, y--;
            cout << dfs1(x, y) << "\n";
        } else {
            ll d;
            cin >> d;
            PII ans = dfs2(d);
            cout << ans.first << " " << ans.second << "\n";
        }
    }
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
    
