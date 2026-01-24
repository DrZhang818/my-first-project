#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

vector<int> w;

ll cal(vector<int> cnt) {
    ll res = 0;
    for(int i = 0; i < cnt.size(); i++) {
        res += 1LL * w[i] * cnt[i];
    }
    return res;
}

struct Info {
    vector<int> vec;
    friend bool operator < (const Info &a, const Info &b) {
        return cal(a.vec) < cal(b.vec);
    }
};

void solve() {  
    int n, k, x;
    cin >> n >> k >> x;
    w.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> w[i];
    }
    sort(w.begin(), w.end(), greater<int>());
    priority_queue<Info> q;
    vector<int> init(n);
    init[0] = k;
    q.push({init});
    set<vector<int>> st;
    while(x > 0) {
        x--;
        auto u = q.top().vec; q.pop();
        ll cur = cal(u);
        cout << cur << "\n";
        for(int i = 0, s = 0; i < n - 1; i++) {
            if(u[i]) {
                s++;
                auto v = u;
                v[i] -= 1;
                v[i + 1] += 1;
                if(st.contains(v)) {
                    continue;
                }
                q.push({v});
                st.insert(v);
            }
            if(s >= 2) {
                break;
            }
        }
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
