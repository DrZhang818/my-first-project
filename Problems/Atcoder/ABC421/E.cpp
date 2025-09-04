#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct State {
    int round;
    vector<int> keep;
    friend bool operator == (const State &a, const State &b) {
        if(a.round != b.round || a.keep.size() != b.keep.size()) {
            return false;
        }
        for(int i = 0; i < a.keep.size(); i++) {
            if(a.keep[i] != b.keep[i]) {
                return false;
            }
        }
        return true;
    }
    State() : round{0}, keep{} {}
};

struct Hash {
    ull operator()(const State &d) const {
        ull res = d.round;
        for(int i = 0; i < d.keep.size(); i++) {
            res = res * 7 * d.keep[i];
        }
        for(int i = d.keep.size(); i < 5; i++) {
            res = res * 7;
        }
        return res;
    };
};

int mi_6[6];

void solve() {
    vector<int> A(7);
    for(int i = 1; i <= 6; i++) {
        cin >> A[i];
    }
    unordered_map<State, db, Hash> dp;
    auto dfs = [&](auto &&self, State &cur) -> db {
        if(cur.round == 3) {
            unordered_map<int,int> cnt;
            for(int i = 0; i < 5; i++) {
                cnt[A[cur.keep[i]]]++;
            }
            int mx = 0;
            for(auto [x, c] : cnt) {
                mx = max(mx, c * x);
            }
            return mx;
        }
        if(dp.contains(cur)) {
            return dp[cur];
        }
        db res = 0;
        int num = 5 - cur.keep.size();
        int tot = mi_6[num];
        for(int i = 0; i < tot; i++) {
            if(cur.round == 2) {
                State nxt = cur;
                nxt.round++;
                for(int j = 0, x = i; j < num; j++, x /= 6) {
                    nxt.keep.push_back(x % 6 + 1);
                }
                res += self(self, nxt);
            } else {
                vector<int> idx(num);
                for(int j = 0, x = i; j < num; j++, x /= 6) {
                    idx[j] = x % 6 + 1;
                }
                db mx = 0;
                for(int s = 0; s < 1 << num; s++) {
                    State nxt = cur;
                    nxt.round++;
                    for(int j = 0; j < num; j++) {
                        if(s >> j & 1) {
                            nxt.keep.push_back(idx[j]);
                        }
                    }
                    mx = max(mx, self(self, nxt));
                }
                res += mx;
            }
        }
        return dp[cur] = res / tot;
    };
    State a;
    cout << fixed << setprecision(12) << dfs(dfs, a) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    mi_6[0] = 1;
    for(int i = 1; i < 6; i++) {
        mi_6[i] = mi_6[i - 1] * 6;
    }
    while(t--) {
        solve();
    }
    return 0;
}
