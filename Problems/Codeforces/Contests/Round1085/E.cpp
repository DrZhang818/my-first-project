#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    a[0] = n;

    if(!is_sorted(a.begin(), a.end(), greater())) {
        cout << "NO\n";
        return;
    }

    vector<int> vis(n + 1);
    for(int i = 1; i <= n; i++) {
        vis[a[i]] = true;
    }

    vector<int> ans(n + 1);
    for(int i = n, j = 0; i >= 1; i--) {
        if(a[i] == a[i - 1]) {
            while(j <= n && vis[j]) j++;
            if(j >= a[i]) {
                cout << "NO\n";
                return;    
            }
            ans[i] = j++;
        } else {
            ans[i] = n + 1;
        }
    }

    cout << "YES\n";
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
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
