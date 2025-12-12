#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

class DSU {
private:
    vector<int> fa;
    vector<ll> area;
    int K;
public:
    DSU(){}
    DSU(int n) {
        fa.resize(n);
        area.assign(n, {});
        K = n;
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) {
        if(x != fa[x]) {
            fa[x] = find(fa[x]);
        }
        return fa[x];
    }
    void setArea(int o, ll x) {
        area[o] = x;
    }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y) {
            return false;
        }
        area[x] += area[y];
        fa[y] = x;
        K -= 1;
        return true;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    ll getArea(int x) {
        return area[find(x)];
    }
    int kinds() {
        return K;
    }
};

struct Rect {
    ll lo[2], hi[2];
    ll area() const {
        return (hi[0] - lo[0] + 1) * (hi[1] - lo[1] + 1);
    }
};

void solve() {  
    int n;
    ll x, y;
    cin >> n >> x >> y;

    vector<Rect> rec;
    rec.push_back({ {0, 0}, {x - 1, y - 1} });

    for(int i = 1; i <= n; i++) {
        char op;
        int a, b;
        cin >> op >> a >> b;
        
        int d = (op == 'Y');
        int od = 1 - d;
        vector<Rect> nrec;
        nrec.reserve(rec.size() * 2);
        for(const auto& r : rec) {
            Rect r1 = r, r2 = r;
            if(r.hi[d] < a) {
                r1.lo[od] -= b;
                r1.hi[od] -= b;
                nrec.push_back(r1);
            } else if(r.lo[d] >= a) {
                r1.lo[od] += b;
                r1.hi[od] += b;
                nrec.push_back(r1);
            } else {
                r1.hi[d] = a - 1;
                r1.lo[od] -= b;
                r1.hi[od] -= b;
                nrec.push_back(r1);

                r2.lo[d] = a;
                r2.lo[od] += b;
                r2.hi[od] += b;
                nrec.push_back(r2);
            }
        }
        rec = move(nrec);
    }

    int m = rec.size();
    DSU dsu(m);
    for(int i = 0; i < m; i++) {
        dsu.setArea(i, rec[i].area());
    }
    auto work = [&](int d) {
        int od = 1 - d;
        map<ll, vector<int>> start, end;
        for(int i = 0; i < m; i++) {
            start[rec[i].lo[d]].push_back(i);
            end[rec[i].hi[d]].push_back(i);
        }
        for(auto [cur, point] : end) {
            if(start.contains(cur))
        }
    };
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
