#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc408/tasks/abc408_f
vector<int> tr;
inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; } 
void init(int n) {
    tr.resize(n << 2);
}
void push_up(int o) {
    tr[o] = max(tr[ls(o)], tr[rs(o)]);
}   
void update(int L, int R, int o, int l, int r, int d) {
    if(l == r) {
        tr[o] = d;
        return;
    }
    int mid = l + r >> 1;
    if(L <= mid) update(L, R, ls(o), l, mid, d);
    if(R > mid) update(L, R, rs(o), mid + 1, r, d);
    push_up(o);
}
int query(int L, int R, int o, int l, int r) {
    if(L <= l && r <= R) {
        return tr[o];
    }
    int res = 0;
    int mid = l + r >> 1;
    if(L <= mid) res = max(res, query(L, R, ls(o), l, mid));
    if(R > mid) res = max(res, query(L, R, rs(o), mid + 1, r));
    return res;
}
void solve() {
    int n, d, len;
    cin >> n >> d >> len;
    init(n);
    vector<int> a(n + 1), pos(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    vector<int> dp(n + 1);
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        if(i - d >= 1) {
            update(pos[i - d], pos[i - d], 1, 1, n, dp[i - d] + 1);
        }
        int l = max(1, pos[i] - len), r = min(n, pos[i] + len);
        dp[i] = query(l, r, 1, 1, n);
        ans = max(ans, dp[i]);
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
