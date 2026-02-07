#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

vector<int> fa;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) return;
    fa[v] = u;
}
bool same(int u, int v) { return find(u) == find(v); }

class XorBasis {
    vector<int> b;

    int num;
    
    bool canBeZero;
    vector<int> basis;
public:
    XorBasis() {
        b.resize(64);
        num = 0;
        canBeZero = false;
    }
    bool insert(int v) {
        for(int i = b.size() - 1; i >= 0; i--) {
            if(!(v >> i)) {
                continue;
            }
            if(b[i] == 0) {
                b[i] = v;
                num++;
                return true;
            }
            v ^= b[i];
        }
        canBeZero = true;
        return false;
    }
    bool decompose(int v) {
        for(int i = b.size() - 1; i >= 0; i--) {
            if(!(v >> i)) {
                continue;
            }
            if(b[i] == 0) {
                return false;
            }
            v ^= b[i];
        }
        return true;
    }
};

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<int> a(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> a[i];
    }

    fa.resize(n);
    iota(fa.begin(), fa.end(), 0);

    int cnt = 0;

    vector<PII> ans(n - 1);

    XorBasis b;

    for(int i = 1, j = 1; i < n && cnt < n - 1; i++) {
        if(j <= m && i == a[j]) {
            j++;
            continue;
        }
        if(b.decompose(i)) {
            continue;
        }
        b.insert(i);
        for(int s = 0; s < n && cnt < n - 1; s++) {
            if(!same(s, s ^ i)) {
                merge(s, s ^ i);
                ans[cnt] = {s, s ^ i};
                cnt++;
            }
        }
    }

    if(cnt < n - 1) {
        cout << -1 << "\n";
        return;
    }

    for(auto [u, v] : ans) {
        cout << u << " " << v << "\n";
    }
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
