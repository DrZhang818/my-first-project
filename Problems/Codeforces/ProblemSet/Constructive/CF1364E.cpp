#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int gen(int L, int R) {
    return rng() % (R - L + 1) + L;
}

auto query(int i, int j) {
    cout << "? " << i + 1 << " " << j + 1 << endl;
    int res;
    cin >> res;
    return res;
}

auto answer(const vector<int>& ans) {
    cout << "!";
    for(int x : ans) {
        cout << " " << x;
    }
    cout << endl;
}

void solve() {
    int n;
    cin >> n;

    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    shuffle(p.begin(), p.end(), rng);

    auto get = [&](int i) {
        int res = (1 << 11) - 1;
        for(int k = 0; k < 14; k++) {
            int j = gen(0, n - 1);
            while(j == i) j = gen(0, n - 1);
            res &= query(i, j);
            if(res == 0) break;
        }
        return res;
    };

    int c = p[0];
    int val = get(c);
    vector<int> memo(n, -1);

    for(int i = 1; i < n; i++) {
        int u = p[i];
        int res = query(c, u);
        if(res == val) {
            c = u;
            val = get(c);
            memo.assign(n, -1);
        } else {
            memo[u] = res;
        }
    }

    vector<int> ans(n);
    for(int i = 0; i < n; i++) {
        if(i == c) continue;
        if(memo[i] != -1) {
            ans[i] = memo[i];
        } else {
            ans[i] = query(c, i);
        }
    }

    answer(ans);
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
