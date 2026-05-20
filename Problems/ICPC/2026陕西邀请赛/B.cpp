#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    i64 n, x, y;
    cin >> n >> x >> y;
    string s;
    cin >> s;

    i64 T = (x + y) / n;
    i64 rem = (x + y) % n;

    int c1 = count(s.begin(), s.end(), '1');
    int c2 = count(s.begin(), s.end(), '2');

    int pre_c1 = count(s.begin(), s.begin() + rem, '1');
    int pre_c2 = count(s.begin(), s.begin() + rem, '2');

    i64 K = -1, M = -1;

    for(i64 k = c1; k <= c1 + c2; k++) {
        i64 m = y - k * T;
        if(m > k || m < pre_c1 || m > pre_c1 + pre_c2 || k - m < c1 - pre_c1 || k - m > c1 + c2 - pre_c1 - pre_c2) continue;
        if(K == -1 || m < M) {
            tie(K, M) = pair{k, m};
        }
    }

    if(K == -1) {
        cout << -1 << "\n";
        return;
    }

    K -= c1;
    M -= pre_c1;

    for(int i = rem - 1; i >= 0; i--) {
        if(s[i] == '2') {
            if(M > 0) {
                s[i] = '1';
                M--;
                K--;
            } else {
                s[i] = '0';
            }
        }
    }

    for(int i = n - 1; i >= rem; i--) {
        if(s[i] == '2') {
            if(K > 0) {
                s[i] = '1';
                K--;
            } else {
                s[i] = '0';
            }
        }
    }

    assert(K == 0 && M == 0);

    cout << s << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}