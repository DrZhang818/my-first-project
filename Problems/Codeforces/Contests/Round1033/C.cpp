#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    ll n, m;
    cin >> n >> m;
    if(n > m || m > n * (n + 1) / 2) {
        cout << -1 << "\n";
        return;
    }
    vector<int> a(n + 1);
    ll k = m - n;
    for(int i = 1; i <= n; i++) {
        int mx = n - i;
        if(k >= mx) {
            a[i] = mx + 1;
            k -= mx;
        } else {
            if(k == 0) {
                iota(a.begin() + i, a.end(), 1);
            } else {
                a[i] = mx + 1;
                iota(a.begin() + i + 1, a.end(), 1);
                swap(a[i], a[i + k + 1]);
            }
            break;
        }
    }
    cout << a[1] << "\n";
    for(int i = 1; i <= n - 1; i++) {
        cout << a[i] << " " << a[i + 1] << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
