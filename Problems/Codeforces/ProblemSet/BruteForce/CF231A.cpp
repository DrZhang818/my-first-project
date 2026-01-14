#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        if(x + y + z >= 2) {
            ans++;
        }
    }    
    cout << ans << "\n";
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
