#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/1538/F
const int N = 11;
int cnt = 0;
vector<int> num(N);
vector<vector<ll>> memo(N + 1, vector<ll>(N + 1, -1));
ll dfs(int pos, int k, bool lead, bool lim) {
    if(pos == 0) return k + 1;
    ll &res = memo[pos][k];
    if(res != -1 && !lead && !lim) return res;
    ll cur = 0;
    int up = lim ? num[pos] : 9;
    for(int i = 0; i <= up; i++) {
        if(i == 0 && lead) {
            cur += dfs(pos - 1, 0, lead, lim && i == up);
        } else if(i != 9) {
            cur += dfs(pos - 1, 0, false, lim && i == up);
        } else {
            cur += dfs(pos - 1, k + 1, false, lim && i == up);
        }
    }
    if(!lead && !lim) res = cur;
    return cur; 
}
ll work(int x) {
    cnt = 0;
    while(x) {
        num[++cnt] = x % 10;
        x /= 10;
    }
    return dfs(cnt, 0, true, true);
}
void solve() {
    int l, r;
    cin >> l >> r;
    cout << work(r - 1) - work(l - 1) << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
