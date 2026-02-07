#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

vector<int> fa;
int num;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
bool merge(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) return false;
    fa[v] = u;
    num--;
    return true;
}

struct Edge {
    int u = -1;
    int v = -1;
    int w = inf;
};

struct Info {
    int u = -1, root = -1;
    int w = inf;
};

void update(Info& a, Info& b, Info cur) {
    if(cur.w < a.w) {
        if(cur.root != a.root) {
            b = a;
        }
        a = cur;
    } else if(cur.w < b.w && cur.root != a.root) {
        b = cur;
    }
}

void solve() {  
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] %= k;
    }

    fa.resize(n + 1);
    iota(fa.begin(), fa.end(), 0);
    num = n;

    sort(a.begin() + 1, a.end());

    ll ans = 0;

    while(num > 1) {
        vector<Edge> mn(n + 1);
        vector<int> roots;
        for(int i = 1; i <= n; i++) {
            if(find(i) == i) {
                roots.push_back(i);
            }
        }

        {
            Info lo1, lo2;
            for(int i = 1; i <= n; i++) {
                update(lo1, lo2, {i, find(i), a[i]});
                if(lo2.u != -1) break;
            }

            for(int i = 1; i <= n; i++) {
                int root = find(i);
                auto lo = root == lo1.root ? lo2 : lo1;
                if(lo.root != -1) {
                    int w = (a[i] + lo.w) % k;
                    if(w < mn[root].w) {
                        mn[root] = {i, lo.u, w};
                    }
                }
            }
        }

        {
            Info hi1, hi2;
            for(int i = 1, j = n; i <= n; i++) {
                while(j >= 1 && a[j] + a[i] >= k) {
                    update(hi1, hi2, {j, find(j), a[j]});
                    j--;
                }
                int root = find(i);
                auto hi = root == hi1.root ? hi2 : hi1;
                if(hi.root != -1) {
                    int w = (a[i] + hi.w) % k;
                    if(w < mn[root].w) {
                        mn[root] = {i, hi.u, w};
                    }
                }
            }
        }

        bool change = false;
        for(int i : roots) {
            if(mn[i].u != -1 && merge(mn[i].u, mn[i].v)) {
                ans += mn[i].w;
                change = true;
            }
        }
        if(!change) {
            break;
        }
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
