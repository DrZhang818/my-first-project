#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

vector<int> fa;
inline int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
int num;
bool merge(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) return false;
    fa[v] = u;
    num--;
    return true;
}

struct Edge {
    int u = -1, v = -1;
    ll w = numeric_limits<ll>::max();
};

struct Info {
    ll w = numeric_limits<ll>::max();
    int root = -1, id = -1;
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
    int n, d;
    cin >> n >> d;
    fa.assign(n + 1, 0);
    num = n;
    iota(fa.begin(), fa.end(), 0);
    
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<ll> f(n + 1), g(n + 1);
    for(int i = 1; i <= n; i++) {
        f[i] = a[i] - 1LL * i * d;
        g[i] = a[i] + 1LL * i * d;
    }

    ll ans = 0;

    while(num > 1) {
        vector<Edge> mn(n + 1);
        vector<int> roots;
        for(int i = 1; i <= n; i++) {
            if(find(i) == i) {
                roots.push_back(i);
            }
        }

        auto work = [&](const vector<ll>& a, const vector<ll>& b, bool tag) {
            Info mn1, mn2;
            auto range = vector<int>(n);
            iota(range.begin(), range.end(), 1);
            if(tag) {
                reverse(range.begin(), range.end());
            }

            for(int i : range) {
                int root = find(i);
                auto tar = root == mn1.root ? mn2 : mn1;
                if(tar.root != -1) {
                    ll w = b[i] + tar.w;
                    if(w < mn[root].w) {
                        mn[root] = {i, tar.id, w};
                    }
                }
                update(mn1, mn2, {a[i], root, i});
            }
        };

        work(f, g, 0);
        work(g, f, 1);

        bool change = false;
        for(int root : roots) {
            if(mn[root].u != -1 && merge(mn[root].u, mn[root].v)) {
                ans += mn[root].w;
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
    while(t--) {
        solve();
    }
    return 0;
}
