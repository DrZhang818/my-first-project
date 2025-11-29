#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int N = int(1E7);

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] *= N;
        sum += a[i];
    }
    ll S = 100 * N;
    if(sum == S) {
        cout << "Yes\n";
        for(int i = 1; i <= n; i++) {
            cout << a[i] << " \n"[i == n];
        }
    } else if(sum < S) {
        ll need = S - sum;
        for(int i = 1; i <= n; i++) {
            a[i] += min(4999999LL, need);
            need -= min(4999999LL, need);
        }
        if(need) {
            cout << "No\n";
        } else {
            cout << "Yes\n";
            for(int i = 1; i <= n; i++) {
                cout << a[i] << " \n"[i == n];
            }
        }
    } else {
        ll need = sum - S;
        for(int i = 1; i <= n; i++) {
            if(a[i] == 0) {
                continue;
            }
            a[i] -= min(5000000LL, need);
            need -= min(5000000LL, need);
        }
        if(need) {
            cout << "No\n";
        } else {
            cout << "Yes\n";
            for(int i = 1; i <= n; i++) {
                cout << a[i] << " \n"[i == n];
            }
        }
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
