#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, k;
    cin >> n >> k;
    if(k < n || k > 2 * n - 1) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    
    int m = k - n;

    vector<int> ans;
    ans.reserve(2 * n);

    if(m == 0) {
        for(int i = 1; i <= n; i++) {
            ans.push_back(i);
            ans.push_back(i);
        }
    } else {
        ans.push_back(1);
        ans.push_back(2);
        for(int i = 2; i <= m; i++) {
            ans.push_back(i + 1);
            ans.push_back(i - 1);
        }
        ans.push_back(m);
        ans.push_back(m + 1);
        for(int i = m + 2; i <= n; i++) {
            ans.push_back(i);
            ans.push_back(i);
        }
    }

    for(int i = 0; i < 2 * n; i++) {
        cout << ans[i] << " \n"[i == 2 * n - 1];
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
