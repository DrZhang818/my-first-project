#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int x, y, p, q;
    cin >> x >> y >> p >> q;
    using T = tuple<int,int,int,int,int>;
    set<T> st;
    queue<T> que;
    que.push({0, 0, x, y, 0});
    int ans = 0;
    while(!que.empty()) {
        int sz = que.size();
        while(sz--) {
            auto [lx, ly, rx, ry, isleft] = que.front(); que.pop();
            if(lx == x && isleft) {
                cout << ans << "\n";
                return;
            }
            if(isleft) {
                int nlx, nly, nrx, nry, ns = 0;
                for(int a = 0; a <= min(p, lx); a++) {
                    for(int b = 0; b <= min(p - a, ly); b++) {
                        if(lx - a == 0 || lx - a + q >= ly - b) {
                            nlx = lx - a;
                            nly = ly - b;
                            nrx = rx + a;
                            nry = ry + b;
                            T cur = {nlx, nly, nrx, nry, ns};
                            if(st.contains(cur)) {
                                continue;
                            }
                            st.insert(cur);
                            que.push(cur);
                        }
                    }
                }
            } else {
                int nlx, nly, nrx, nry, ns = 1;
                for(int a = 0; a <= min(p, rx); a++) {
                    for(int b = 0; b <= min(p - a, ry); b++) {
                        if(rx - a == 0 || rx - a + q >= ry - b) {
                            nlx = lx + a;
                            nly = ly + b;
                            nrx = rx - a;
                            nry = ry - b;
                            T cur = {nlx, nly, nrx, nry, ns};
                            if(st.contains(cur)) {
                                continue;
                            }
                            st.insert(cur);
                            que.push(cur);
                        }
                    }
                }
            }
        }
        ans++;
         
    }
    cout << -1 << "\n";

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
