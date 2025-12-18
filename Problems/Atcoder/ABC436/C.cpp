#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

PII dir[] = {{0,0},{0,1},{1,0},{1,1}};

void solve() {  
    int n, m;
    cin >> n >> m;
    set<PII> st;
    int ans = 0;
    for(int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        bool ok = true;
        for(auto [dx, dy] : dir) {
            int nx = x + dx;
            int ny = y + dy;
            if(st.contains({nx, ny})) {
                ok = false;
                break;
            }
        }
        if(ok) {
            ans++;
            for(auto [dx, dy] : dir) {
                int nx = x + dx;
                int ny = y + dy;
                st.insert({nx, ny});
            }   
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
