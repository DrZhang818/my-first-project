#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    vector<vector<int>> a(3, vector<int>(3));
    vector<int> vis(10);
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cin >> a[i][j];
            vis[a[i][j]] = 1;
        }
    }

    for(int i = 1; i <= 9; i++) {
        if(!vis[i]) {
            cout << "No\n";
            return;
        }
    }

    for(int i = 0; i < 3; i++) {
        int sum = accumulate(a[i].begin(), a[i].end(), 0);
        if(sum != 15) {
            cout << "No\n";
            return;
        }
    }

    for(int j = 0; j < 3; j++) {
        int cur = 0;
        for(int i = 0; i < 3; i++) {
            cur += a[i][j];
        }
        if(cur != 15) {
            cout << "No\n";
            return;
        }
    }

    if(a[0][0] + a[1][1] + a[2][2] != 15 || a[0][2] + a[1][1] + a[2][0] != 15) {
        cout << "No\n";
        return;
    }

    cout << "Yes\n";
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
