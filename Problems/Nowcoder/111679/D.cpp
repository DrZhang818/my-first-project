#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1E9;

//https://ac.nowcoder.com/acm/contest/111679/D

struct info {
    int l, r;
    friend bool operator < (const info &a, const info &b) {
        return a.l < b.l;
    }
};
int sz;
vector<int> mx, tag;
inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; } 
void push_up(int o) {
    mx[o] = max(mx[ls(o)], mx[rs(o)]);
}
void addtag(int o, int d) {
    tag[o] += d;
    mx[o] += d;
}
void push_down(int o) {
    if(tag[o]) {
        addtag(ls(o), tag[o]);
        addtag(rs(o), tag[o]);
        tag[o] = 0;
    }
}
void update(int L, int R, int o, int l, int r, int d) {
    if(L <= l && r <= R) {
        addtag(o, d);
        return;
    }
    push_down(o);
    int mid = l + (r - l) / 2;
    if(L <= mid) update(L, R, ls(o), l, mid, d);
    if(R > mid) update(L, R, rs(o), mid + 1, r, d);
    push_up(o);
}
int query(int L, int R, int o, int l, int r) {
    if(L <= l && r <= R) return mx[o];
    push_down(o);
    int res = -inf;
    int mid = l + (r - l) / 2;
    if(L <= mid) res = max(res, query(L, R, ls(o), l, mid));
    if(R > mid) res = max(res, query(L, R, rs(o), mid + 1, r));
    return res;
}
void solve() {
    int n, k;
    cin >> n >> k;
    vector<info> a(n);
    vector<int> val{0};
    for(int i = 0; i < n; i++) {
        cin >> a[i].l >> a[i].r;
        a[i].r += k;
        val.push_back(a[i].l);
        val.push_back(a[i].r);
    }
    sort(a.begin(), a.end());
    sort(val.begin() + 1, val.end());
    val.erase(unique(val.begin() + 1, val.end()), val.end());
    sz = val.size();
    mx.assign(sz << 2, 0);
    tag.assign(sz << 2, 0);
    priority_queue<PII, vector<PII>, greater<PII>> q;
    int ans = 0;
    for(auto [l, r] : a) {
        while(!q.empty() && q.top().first < l) {
            auto [R, L] = q.top(); q.pop();
            L = lower_bound(val.begin() + 1, val.end(), L) - val.begin();
            R = lower_bound(val.begin() + 1, val.end(), R) - val.begin();
            update(L, R, 1, 1, sz, 1);
        }
        q.push({r, l});
        int cur = q.size();
        ans = max(ans, cur + query(1, sz, 1, 1, sz));
    }
    cout << ans << "\n";
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
