#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

struct State {
    int id, rem;

    auto operator<=>(const State& o) const {
        if(id != o.id) return id <=> o.id;
        return o.rem <=> rem;
    }
    bool operator==(const State&) const = default;
};

void solve() {
    int N, M, C;
    cin >> N >> M >> C;
    vector<int> H(N), D(N);
    for(int i = 0; i < N; i++) {
        cin >> H[i] >> D[i];
    }
    vector<State> dp(C + 1, State(0, H[0]));
    for(int i = 0; i < M; i++) {
        int h, d, c;
        cin >> h >> d >> c;
        for(int j = c; j <= C; j++) {
            auto [id, rem] = dp[j];
            int p = id % N;
            i64 t = D[p] == 0 ? inf : (h - 1) / D[p];
            if(d * t >= rem) {
                dp[j - c] = max(dp[j - c], State(id + 1, H[(id + 1) % N]));
            } else {
                dp[j - c] = max(dp[j - c], State(id, rem - d * t));
            }
        }
    }

    vector<i64> pre(N + 1);
    for(int i = 0; i < N; i++) {
        pre[i + 1] = pre[i] + H[i];
    }

    int id = dp[0].id;
    i64 cur = H[id % N] - dp[0].rem;
    i64 tot = pre[N] * (id / N) + pre[id % N] + cur;

    cout << cur << " " << tot << "\n";
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
