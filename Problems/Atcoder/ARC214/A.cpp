#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<string> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for(int s = 0; s < 2 * n - 1; s++) {
        int x = -1;
        for(int i = 0; i < n; i++) {
            int j = s - i;
            if(j < 0 || j >= n) continue;
            if(a[i][j] != '?') {
                if(x == -1) {
                    x = a[i][j] - '0';
                } else if(a[i][j] - '0' != x) {
                    cout << -1 << "\n";
                    return;
                }
            }
        }
        if(x == -1) x = 0;
        for(int i = 0; i < n; i++) {
            int j = s - i;
            if(j < 0 || j >= n) continue;
            a[i][j] = char(x + '0');
        }
    }

    for(int i = 0; i < n; i++) {
        cout << a[i] << "\n";
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
