#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

// struct info {
//     int x, y;
//     friend bool operator < (const info &a, const info &b) {
//         if(a.x + a.y != b.x + b.y) return a.x + a.y < b.x + b.y;
//         return a.x < b.x;
//     }
// };
void solve() {
    int u = 1, v = 2;
    set<PII> st;
    st.insert({u, v});
    auto dfs = [&](this auto &&self, int x, int y) -> void {
        if(x >= 200 || y >= 200) return;
        int d = max(x, y);
        int nx = x + d, ny = y;
        if(nx < 200 && ny < 200) {
            if(!st.count({x + d, y})) {
                st.insert({x + d, y});
                self(x + d, y);
            }
        }
        nx = x, ny = y + d;
        if(nx < 200 && ny < 200) {
            if(!st.count({x, y + d})) {
                st.insert({x, y + d});
                self(x, y + d);
            }
        }
    };
    dfs(u, v);
    for(auto [u, v] : st) {
        cerr << u << " " << v << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
