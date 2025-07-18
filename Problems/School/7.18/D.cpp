#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        if(i % 2 != a[i] % 2) {
            cout << "No\n";
            return;
        }
    }
    for(int i = 2; i <= n - 1; i++) {
        if(a[i - 1] > a[i + 1]) {
            if(a[i] > a[i - 1] || a[i] < a[i + 1]) {
                cout << "No\n";
                return;
            }
            swap(a[i - 1], a[i + 1]);
        }
    }
    cout << "Yes\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
