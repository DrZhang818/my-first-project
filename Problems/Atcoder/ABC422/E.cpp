#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int get(int L, int R) {
    return rnd() % (R - L + 1) + L;
}

struct info {
    ll x, y;
};

void solve() {
    int n;
    cin >> n;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    for(int t = 1; t <= 100; t++) {
        int i = -1, j = -1;
        while(i == j) {
            i = get(1, n);
            j = get(1, n);
        }
        auto [x1, y1] = a[i];
        auto [x2, y2] = a[j];
        ll A = y1 - y2;
        ll B = x2 - x1;
        ll C = x1 * y2 - x2 * y1;
        int cnt = 0;
        for(int i = 1; i <= n; i++) {
            auto [x, y] = a[i];
            if(A * x + B * y + C == 0) {
                cnt++;
            }
        }
        if(cnt > n / 2) {
            cout << "Yes\n";
            cout << A << " " << B << " " << C << "\n";
            return;
        }
    }
    cout << "No\n";
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
