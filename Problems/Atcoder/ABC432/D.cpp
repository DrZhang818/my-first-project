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
    vector<ll> cnt;
    int K;
public:
    DSU(){}
    DSU(int n) {
        fa.resize(n);
        cnt.assign(n, {});
        K = n;
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) {
        if(x != fa[x]) {
            fa[x] = find(fa[x]);
        }
        return fa[x];
    }
    void setCnt(int o, ll x) {
        cnt[o] = x;
    }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y) {
            return false;
        }
        cnt[x] += cnt[y];
        fa[y] = x;
        K -= 1;
        return true;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    ll getCnt(int x) {
        return cnt[find(x)];
    }
    int kinds() {
        return K;
    }
};

struct info {
    ll x1, y1, x2, y2;
};

struct line {
    ll v;
    int op, id;
    friend bool operator < (const line& a, const line& b) {
        if(a.v != b.v) return a.v < b.v;
        return a.op > b.op;
    }
};

void solve() {  
    int n, x, y;
    cin >> n >> x >> y;

    vector<info> rec;
    rec.push_back({0, 0, x - 1, y - 1});

    for(int i = 1; i <= n; i++) {
        char op;
        cin >> op;
        int a, b;
        cin >> a >> b;
        vector<info> nrec;
        nrec.reserve(rec.size() * 2);
        if(op == 'X') {
            for(auto& [x1, y1, x2, y2] : rec) {
                if(x2 < a) {
                    nrec.emplace_back(x1, y1 - b, x2, y2 - b);
                } else if(x1 >= a) {
                    nrec.emplace_back(x1, y1 + b, x2, y2 + b);
                } else {
                    nrec.emplace_back(x1, y1 - b, a - 1, y2 - b);
                    nrec.emplace_back(a, y1 + b, x2, y2 + b);
                }
            }
        } else {
            for(auto& [x1, y1, x2, y2] : rec) {
                if(y2 < a) {
                    nrec.emplace_back(x1 - b, y1, x2 - b, y2);
                } else if(y1 >= a) {
                    nrec.emplace_back(x1 + b, y1, x2 + b, y2);
                } else {
                    nrec.emplace_back(x1 - b, y1, x2 - b, a - 1);
                    nrec.emplace_back(x1 + b, a, x2 + b, y2);
                }
            }
        }
        swap(rec, nrec);
        // rec = move(nrec);
    }
    int m = rec.size();

    DSU g(m);
    vector<line> Line;
    Line.reserve(m);
    for(int i = 0; i < m; i++) {
        auto [x1, y1, x2, y2] = rec[i];
        g.setCnt(i, (x2 - x1 + 1) * (y2 - y1 + 1));
        Line.push_back({y1, 1, i});
        Line.push_back({y2, 0, i});
    }
    sort(Line.begin(), Line.end());
    map<ll,int> mp;
    for(auto [y, op, id] : Line) {
        auto [x1, _, x2, __] = rec[id];
        if(op == 1) {
            mp[x1] = id;
            mp[x2] = id;
            if(mp.contains(x1 - 1)) {
                g.merge(id, mp[x1 - 1]);
            }
            if(mp.contains(x2 + 1)) {
                g.merge(id, mp[x2 + 1]);
            }
        } else {
            mp.erase(x1);
            mp.erase(x2);
        }
    }

    Line.clear();
    mp.clear();
    Line.reserve(m);
        for(int i = 0; i < m; i++) {
        auto [x1, y1, x2, y2] = rec[i];
        Line.push_back({x1, 1, i});
        Line.push_back({x2, 0, i});
    }
    sort(Line.begin(), Line.end());
    for(auto [x, op, id] : Line) {
        auto [_, y1, __, y2] = rec[id];
        if(op == 1) {
            mp[y1] = id;
            mp[y2] = id;
            if(mp.contains(y1 - 1)) {
                g.merge(id, mp[y1 - 1]);
            }
            if(mp.contains(y2 + 1)) {
                g.merge(id, mp[y2 + 1]);
            }
        } else {
            mp.erase(y1);
            mp.erase(y2);
        }
    }

    int cnt = g.kinds();
    cout << cnt << "\n";
    vector<ll> val;
    val.reserve(cnt);
    for(int i = 0; i < m; i++) {
        if(g.find(i) == i) {
            val.push_back(g.getCnt(i));
        }
    }
    sort(val.begin(), val.end());
    for(int i = 0; i < cnt; i++) {
        cout << val[i] << " \n"[i == cnt - 1];
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
