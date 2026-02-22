#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

int C[30][30];

int binom(int n, int k) {
    if(n < 0 || k > n) return 0;
    return C[n][k];
}

void solve() {  
    int n;
    cin >> n;
    vector<vector<int>> a(n + 1, vector<int>(n + 1));

    for(int s = 2; s <= 2 * n; s++) {
        int x = 0;
        for(int i = n; i >= 1; i--) {
            int j = s - i;
            if(j < 1 || j > n) continue;
            a[i][j] = x;
            x += binom(2 * n - i - j - 1, n - j - 1);
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cout << a[i][j] << " \n"[j == n];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 0; i <= 29; i++) {
        for(int j = 0; j <= 29; j++) {
            if(j == 0) C[i][j] = 1;
            else C[i][j] = C[i - 1][j - 1] + C[i - 1][j]; 
        }
    }

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
