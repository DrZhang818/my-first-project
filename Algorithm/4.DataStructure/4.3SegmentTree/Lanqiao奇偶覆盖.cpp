#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


struct line {
    int x1, x2, y, tag;
    friend bool operator < (const line &a, const line &b) {
        return a.y < b.y;
    }
};
vector<int> cnt, len1, len2, X;
vector<line> L;
inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; }
void push_up(int o, int l, int r) {
    if(cnt[o] & 1) {
        len2[o] = len1[ls(o)] + len1[rs(o)];
        len1[o] = X[r + 1] - X[l] - len2[o];
    } else if(cnt[o] != 0) {
        len1[o] = len1[ls(o)] + len1[rs(o)];
        len2[o] = X[r + 1] - X[l] - len1[o];
    } else {
        len1[o] = len1[ls(o)] + len1[rs(o)];
        len2[o] = len2[ls(o)] + len2[rs(o)];
    }
}
void update(int L, int R, int o, int l, int r, int flag) {
    if(L <= l && r <= R) {
        cnt[o] += flag;
    } else {
        int mid = l + r >> 1;
        if(L <= mid) update(L, R, ls(o), l, mid, flag);
        if(R > mid) update(L, R, rs(o), mid + 1, r, flag);
    }
    push_up(o, l, r);
}
void solve() { 
    int n;
    cin >> n;
    int event_cnt = n * 2;
    cnt.resize(event_cnt << 3);
    len1.resize(event_cnt << 3);
    len2.resize(event_cnt << 3);
    X.resize(event_cnt + 1);
    L.resize(event_cnt + 1);
    for(int i = 1; i <= n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        L[i] = {x1, x2, y1, 1};
        L[n + i] = {x1, x2, y2, -1};
        X[i] = x1;
        X[n + i] = x2;
    }
    sort(L.begin() + 1, L.end());
    sort(X.begin() + 1, X.end());
    X.erase(unique(X.begin() + 1, X.end()), X.end());
    int m = X.size() - 1;
    ll ans1 = 0, ans2 = 0;
    for(int i = 1; i < event_cnt; i++) {
        int l = L[i].x1, r = L[i].x2;
        l = lower_bound(X.begin() + 1, X.end(), l) - X.begin();
        r = lower_bound(X.begin() + 1, X.end(), r) - X.begin();
        update(l, r - 1, 1, 1, m - 1, L[i].tag);
        ans1 += (ll)(L[i + 1].y - L[i].y) * len1[1];
        ans2 += (ll)(L[i + 1].y - L[i].y) * len2[1]; 
    }
    cout << ans1 << "\n" << ans2 << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
