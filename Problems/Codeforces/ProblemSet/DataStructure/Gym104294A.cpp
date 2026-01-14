#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void chmin(int &x, int y) {
    if(x > y) {
        x = y;
    }
}

void solve() {  
    int n, q;
    cin >> n >> q;
    vector a(n + 1, vector<int>(n + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    vector<vector<int>> R(n + 1, vector<int>(n * n + 1, inf));

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            for(int k = 1; k <= n; k++) {
                if(i + k - 1 > n || j + k - 1 > n) break;
                chmin(R[k][a[i][j]], a[i + k - 1][j + k - 1]);
            }
        }
    }

    for(int k = 1; k <= n; k++) {
        for(int s = n * n - 1; s >= 0; s--) {
            chmin(R[k][s], R[k][s + 1]);
        }
    }


    while(q--) {
        int l, r;
        cin >> l >> r;
        for(int k = n; k >= 1; k--) {
            if(R[k][l] <= r){
                cout << k * k << "\n";
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
