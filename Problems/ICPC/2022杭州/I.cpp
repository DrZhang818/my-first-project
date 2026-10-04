#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;
constexpr int R = 3000;
constexpr int B = 3000;
constexpr int G = 4000;

auto query(int x) {
    cout << "walk " << x << endl;
    int res;
    cin >> res;
    return res;
}

auto answer(int n) {
    cout << "guess " << n << endl;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> gen(0, 1'000'000'000);

void solve() {
    int m = 0, v = 0;
    for(int i = 1; i <= R; i++) {
        v = query(gen(rng));
        m = max(m, v);
    }

    map<int, int> pos;
    pos[v] = 0;

    for(int i = 1; i < B; i++) {
        v = query(1);
        if(pos.contains(v)) {
            answer(i - pos[v]);
            return;
        }
        pos[v] = i;
    }

    i64 s = B - 1;
    for(int i = 0; i < G; i++) {
        int x = i == 0 ? m : B;
        v = query(x);
        s += x;
        if(pos.contains(v)) {
            answer(s - pos[v]);
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
