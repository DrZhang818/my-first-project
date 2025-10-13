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
    vector<int> a(n), p(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    iota(p.begin(), p.end(), 1);
    do {
        bool ok = true;
        for(int i = 0; i < n; i++) {
            if(a[i] != -1 && a[i] != p[i]) {
                ok = false;
                break;
            }
        }
        if(ok) {
            cout << "Yes\n";
            for(int i = 0; i < n; i++) {
                cout << p[i] << " \n"[i == n - 1];
            }
            return;
        }
    } while (next_permutation(p.begin(), p.end()));
    cout << "No\n";
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
