#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> vis(n);
    vector<pair<int,int>> ans {};

    for(int s = n - 1; s >= 1; s--) {
        vector<int> las(s, -1);
        for(int i = 0; i < n; i++) {
            if(vis[i]) {
                continue;
            }
            int rem = a[i] % s;
            if(las[rem] == -1) {
                las[rem] = i;
            } else {
                ans.emplace_back(las[rem], i);
                vis[i] = true;
                break;
            }
        }
    }    
    reverse(ans.begin(), ans.end());

    cout << "YES\n";

    for(int i = 0; i < n; i++) {
        if(!vis[i]) {
            cout << i + 1 << "\n";
            break;
        }
    }

    for(auto [x, y] : ans) {
        cout << x + 1 << " " << y + 1 << "\n";
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
