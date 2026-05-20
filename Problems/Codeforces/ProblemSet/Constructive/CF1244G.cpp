#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    i64 n, k;
    cin >> n >> k;

    i64 lo = n * (n + 1) / 2;
    if(k < lo) {
        cout << -1 << "\n";
        return;
    }

    vector<int> p(n + 1), q(n + 1);

    i64 sum = 0;
    vector<int> tar(n + 1);
    for(int i = n, v = n; i >= 1; i -= 2, v--) {
        tar[i] = tar[i - 1] = v;
        sum += v + (i >= 2 ? v : 0);
    }

    for(int i = 1; i <= n; i++) {
        auto d = min<i64>(tar[i] - i, sum - k);
        if(d <= 0) break;
        tar[i] -= d;
        sum -= d;
    }

    int idx = -1;
    for(int i = 1; i <= n; i++) {
        if(tar[i] == i) {
            p[i] = q[i] = i;
        } else {
            idx = i;
            break;
        }
    }

    if(idx != -1) {
        int mn = inf;
        for(int i = idx, j = n; i <= n; i++, j--) {
            p[i] = i;
            q[i] = j;
            mn = min(mn, max(i, j));
        }

        vector<int> posx(n + 1), posy(n + 1);
        for(int i = 1; i <= n; i++) {
            posx[p[i]] = i;
            posy[q[i]] = i;
        }

        for(int i = mn - 1; i >= tar[idx]; i--) {
            if(p[posx[i]] < q[posx[i]]) {
                swap(p[posx[i]], p[posx[i + 1]]);
                swap(posx[i], posx[i + 1]);
            }
            if(q[posy[i]] < p[posy[i]]) {
                swap(q[posy[i]], q[posy[i + 1]]);
                swap(posy[i], posy[i + 1]);
            }
        }
    }

    cout << sum << "\n";
    for(int i = 1; i <= n; i++) {
        cout << p[i] << " \n"[i == n];
    }
    for(int i = 1; i <= n; i++) {
        cout << q[i] << " \n"[i == n];
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
