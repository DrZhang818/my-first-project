#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int mod(int x, int p) { 
    return (x % p + p) % p;
}

void solve() {  
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    a[0][n / 2] = 1;
    int x = 0, y = n / 2, num = 1;
    for(int i = 0; i < n * n - 1; i++) {
        int nx = mod(x - 1, n);
        int ny = mod(y + 1, n);
        if(a[nx][ny]) {
            nx = mod(x + 1, n);
            ny = y;
        } 
        a[nx][ny] = ++num;
        x = nx, y = ny;
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << a[i][j] << " \n"[j == n - 1];
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
