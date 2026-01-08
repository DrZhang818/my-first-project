#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int a, b;
    cin >> a >> b;
    auto cal = [&](int x, int y) -> int {
        int res = 0;
        for(int k = 1, s = 1; ; k ^= 1, s <<= 1) {
            if(k & 1) {
                x -= s;
            } else {
                y -= s;
            }
            if(x < 0 || y < 0) break;
            res++;
        }
        return res;
    };
    cout << max(cal(a, b), cal(b, a)) << "\n";
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
