#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() { 
    int n = 37; 
    cout << n * n + n + 1 << " " << n + 1 << "\n";

    for(int k = 0; k < n; k++) {
        for(int b = 0; b < n; b++) {
            for(int x = 0; x < n; x++) {
                int y = (k * x + b) % n;
                cout << x * n + y + 1 << " ";
            }
            cout << n * n + k + 1 << "\n";
        }
    }

    for(int c = 0; c < n; c++) {
        for(int y = 0; y < n; y++) {
            cout << c * n + y + 1 << " ";
        }
        cout << n * n + n + 1 << "\n";
    }

    for(int k = 0; k <= n; k++) {
        cout << n * n + k + 1 << " \n"[k == n];
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
