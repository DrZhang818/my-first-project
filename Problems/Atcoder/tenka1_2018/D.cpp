#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr ll inf = ll(1E18);

void solve() {  
    int n;
    cin >> n;
    int m = 1;
    while(m * (m - 1) < 2 * n) {
        m++;
    }
    if(m * (m - 1) != 2 * n) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    cout << m << "\n";
    int id = 1, deg = m - 1;
    vector<vector<int>> ans(m + 1);
    for(int i = 1; i <= m; i++) {
        for(int j = id; j <= id + deg - 1; j++) {
            ans[i].push_back(j);
        }
        for(int j = i + 1; j <= m; j++) {
            ans[j].push_back(id + j - i - 1);
        }
        id += deg;
        deg--;
    }
    for(int i = 1; i <= m; i++) {
        cout << m - 1 << " ";
        for(auto x : ans[i]) {
            cout << x << " \n"[x == ans[i].back()];
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
