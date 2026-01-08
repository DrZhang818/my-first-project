#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int query(int i, int j) {
    cout << "? " << i << " " << j << endl;
    int res;
    cin >> res;
    return res;
}

void solve() {  
    int n;
    cin >> n;
    int N = n * n;
    vector a(n + 1, vector<int>(n + 1));
    int mx = -1, idx = -1;
    vector<int> dis_UL(N + 1);
    vector<int> dis_UR(N + 1);
    for(int i = 2; i <= N; i++) {
        int d = query(1, i);
        dis_UL[i] = d;
        if(d > mx) {
            mx = d;
            idx = i;
        }
    }

    if(mx == 2 * n - 2) {
        a[1][1] = 1;
        idx = idx == 2 ? idx + 1 : idx - 1;
        int mx = -1, p = -1;
        for(int i = 2; i <= N; i++) {
            if(dis_UL[i] == n - 1) {
                int x = query(i, idx);
                if(x > mx) {
                    mx = x;
                    p = i;
                }
            }
        }
        a[1][n] = p;
    } else {
        a[1][1] = idx;
        auto t = dis_UL;
        for(int i = 1; i <= N; i++) {
            dis_UL[i] = query(idx, i);
        }
        int mx = -1, p = -1;
        for(int i = 1; i <= N; i++) {
            if(dis_UL[i] == n - 1) {
                int x = t[i];
                if(x > mx) {
                    mx = x;
                    p = i;
                }
            }
        }
        a[1][n] = p;
    }
    for(int i = 1; i <= N; i++) {
        dis_UR[i] = query(a[1][n], i);
    }

    int u = a[1][1], v = a[1][n];
    for(int i = 1; i <= N; i++) {
        int d1 = dis_UL[i], d2 = dis_UR[i];
        int x = (d1 + d2 - n + 3) / 2;
        int y = d1 + 2 - x;
        a[x][y] = i;
    }

    cout << "!" << endl;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
