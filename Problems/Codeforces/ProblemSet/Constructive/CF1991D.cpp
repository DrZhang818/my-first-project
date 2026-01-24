#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

vector<int> a{0, 1, 2, 2, 3, 3};

void solve() {  
    int n;
    cin >> n;
    if(n <= 5) {
        cout << a[n] << "\n";
        for(int i = 1; i <= n; i++) {
            cout << a[i] << " \n"[i == n];
        }
        return ;
    }
    vector<int> ans(n + 1);
    for(int i = 1; i <= n; i++) {
        ans[i] = i % 4 + 1;
    }
    cout << 4 << "\n";
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
