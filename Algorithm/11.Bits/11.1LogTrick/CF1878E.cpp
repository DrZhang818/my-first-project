#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//ST + 二分
void solve1() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    const int N = log2(n);
    vector st(n + 1, vector<int>(N + 1));
    for(int i = 1; i <= n; i++) {
        st[i][0] = a[i];
    }
    for(int s = 1; s <= N; s++) {
        for(int i = 1; i + (1 << s - 1) <= n; i++) {
            st[i][s] = st[i][s - 1] & st[i + (1 << s - 1)][s - 1];
        }
    }
    int q;
    cin >> q;
    while(q--) {
        int L, k;
        cin >> L >> k;
        if(a[L] < k) {
            cout << -1 << " ";
        } else {
            int l = L - 1, r = n + 1;
            while(l + 1 < r) {
                int mid = l + r >> 1;
                int len = log2(mid - L + 1);
                int x = st[L][len] & st[mid - (1 << len) + 1][len];
                if(x >= k) {
                    l = mid;
                } else {
                    r = mid;
                }
            } 
            cout << l << " ";
        }
    }
    cout << "\n";
}


//LogTrick解法
struct info {
    int l, k;
};
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int q;
    cin >> q;
    vector<info> Q(q + 1);
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= q; i++) {
        cin >> Q[i].l >> Q[i].k;
        adj[Q[i].l].push_back(i);
    }
    auto get = [&](int L, int k) -> int {
        int res = L;
        int l = L - 1, r = n + 1;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            if(a[mid] >= k) {
                l = mid;
            } else {
                r = mid;
            }
        }
        return l;
    };
    vector<int> ans(q + 1);
    for(int l = n; l >= 1; l--) {
        for(int r = l + 1; r <= n && (a[r] & a[l]) != a[r]; r++) {
            a[r] &= a[l];
        }
        for(int x : adj[l]) {
            int k = Q[x].k;
            if(a[l] < k) {
                ans[x] = -1;
            } else {
                ans[x] = get(l, k);
            }
        }
    }
    for(int i = 1; i <= q; i++) {
        cout << ans[i] << " \n"[i == q];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve1();
    }
    return 0;
}
