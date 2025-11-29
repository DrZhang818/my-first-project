#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int l, r;
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> c(n + 2);
    vector<info> a(m + 1);
    vector<bool> L(n + 1), R(n + 1);
    for(int i = 1; i <= m; i++) {
        cin >> a[i].l >> a[i].r;
        c[a[i].l]++;
        c[a[i].r + 1]--;
        L[a[i].l] = 1;
        R[a[i].r] = 1;
    }
    for(int i = 1; i <= n; i++) {
        c[i] += c[i - 1];
    }
    for(int i = 1; i <= n; i++) {
        if(c[i] == m) {
            for(int j = 1, s = 1; j <= n; j++) {
                if(j == i) {
                    cout << 0 << " ";
                } else {
                    cout << s << " ";
                    s++;
                }
            }
            cout << "\n";
            return;
        }
    }
    for(int i = 1; i <= n; i++) {
        if(c[i] == 0) {
            for(int j = 1, s = 1; j <= n; j++) {
                if(j == i) {
                    cout << 0 << " ";
                } else {
                    cout << s << " ";
                    s++;
                }
            }
            cout << "\n";
            return;
        }
    }
    for(int i = 1; i <= n; i++) {
        if(L[i] != 1 || R[i] != 1) {
            vector<int> pos(n + 1, -1);
            pos[i] = 0;
            if(L[i] == 1) {
                if(i + 1 <= n) {
                    pos[i + 1] = 1;
                } else {
                    pos[i - 1] = 1;
                }
            } else if(R[i] == 1) {
                if(i - 1 >= 1) {
                    pos[i - 1] = 1;
                } else {
                    pos[i + 1] = 1;
                }
            } else {
                if(i + 1 <= n) {
                    pos[i + 1] = 1;
                } else {
                    pos[i - 1] = 1;
                }
            }
            int cur = 2;
            for(int i = 1; i <= n; i++) {
                if(pos[i] == -1) {
                    pos[i] = cur++;
                }
            }
            for(int i = 1; i <= n; i++) {
                cout << pos[i] << " \n"[i == n];
            }
            return;
        }
    }
    vector<int> pos(n + 1);
    pos[1] = 0;
    pos[n] = 1;
    for(int i = 2; i < n; i++) {
        pos[i] = i;
    }
    for(int i = 1; i <= n; i++) {
        cout << pos[i] << " \n"[i == n];
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
