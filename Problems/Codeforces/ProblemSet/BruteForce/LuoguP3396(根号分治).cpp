#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }    
    int B = sqrt(q);
    vector<vector<int>> sum(B);
    while(q--) {
        char op;
        int x, y;
        cin >> op >> x >> y;
        if(op == 'A') {
            if(x < B) {
                if(sum[x].empty()) {
                    sum[x].resize(x);
                    for(int i = 0; i <= n; i++) {
                        sum[x][i % x] += a[i];
                    }
                }
                cout << sum[x][y] << "\n";
            } else {
                ll sum = 0;
                for(int i = y; i <= n; i += x) {
                    sum += a[i];
                }
                cout << sum << "\n";
            }
        } else {
            int p = a[x];
            a[x] = y;
            for(int b = 1; b < B; b++) {
                if(sum[b].empty()) continue;
                sum[b][x % b] += y - p;
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
