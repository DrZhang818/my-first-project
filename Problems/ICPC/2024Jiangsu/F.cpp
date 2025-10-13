#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, k;
    cin >> n >> k;
    ll cur = 0;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cur += a[i];
        if(i >= k) {
            if((cur + k - 1) / k < 1024) {
                cout << fixed << setprecision(12) << (db)cur / k << "  KiBps" << "\n";
            } else {
                db t = (db) cur / 1024;
                cout << fixed << setprecision(12) << t / k << " MiBps" << "\n";
            }
            cur -= a[i - k + 1];
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
