#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    vector<int> ca(n + 1), cb(n + 1);

    for(int i = 1; i <= k; i++) {
        bool ok = true;
        for(int j = i; j <= n; j += k) {
            if(a[j] != a[i]) {
                ok = false;
                break;
            }
        }

        if(ok) {
            ca[a[i]]++;
            int x = -1;
            for(int j = i; j <= n; j += k) {
                if(b[j] != -1) {
                    if(x == -1) {
                        x = b[j];
                    } else if(b[j] != x) {
                        cout << "NO\n";
                        return;
                    }
                }
            }
            if(x != -1) {
                cb[x]++;
            }
        } else {
            for(int j = i; j <= n; j += k) {
                if(b[j] != -1 && b[j] != a[j]) {
                    cout << "NO\n";
                    return;
                }
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        if(cb[i] > ca[i]) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";    
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
