#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 1000000;

int T[N + 1];
int timer = 0;

auto rev(int x) {
    int res = 0;
    while(x) {
        res = res * 10 + x % 10;
        x /= 10;
    }
    return res;
};

void solve() {  
    int a, b, k;
    cin >> a >> b >> k;

    queue<int> q;
    q.push(a);
    T[a] = timer;

    int ans = 0;
    while(!q.empty()) {
        int sz = q.size();
        while(sz--) {
            int u = q.front(); q.pop();
            if(u == b) {
                cout << ans << "\n";
                return;
            }
            int v = u + k;
            if(v <= N) {
                if(T[v] != timer) {
                    T[v] = timer;
                    q.push(v);
                }
            }
            if(u % 10 != 0) {
                v = rev(u);
                if(T[v] != timer) {
                    T[v] = timer;
                    q.push(v);
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
    cin >> t;
    while(t--) {
        timer++;
        solve();
    }
    return 0;
}
