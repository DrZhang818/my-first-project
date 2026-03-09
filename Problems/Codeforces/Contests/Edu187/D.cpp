#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<int> cx(n + m + 1), cy(n + m + 1);
    i64 LCM = 1;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cx[x]++;
        if(LCM <= n + m) {
            LCM = lcm(LCM, x);
        }
    }
    int mx = 0;
    for(int i = 1; i <= m; i++) {
        int y;
        cin >> y;
        cy[y]++;
        mx = max(mx, y);
    }

    i64 c1 = 0, c2 = 0, c12 = 0;

    vector<bool> ok1(mx + 1), ok2(mx + 1, true);
    for(int i = 1; i <= mx; i++) {
        if(i % LCM == 0) {
            ok2[i] = false;
        }
        if(cx[i] == 0) continue;
        for(int j = i; j <= mx; j += i) {
            ok1[j] = true;            
        }
    }

    for(int i = 1; i <= mx; i++) {
        if(ok1[i]) {
            c1 += cy[i];
        }
        if(ok2[i]) {
            c2 += cy[i];
        }
        if(ok1[i] && ok2[i]) {
            c12 += cy[i];
        }
    }

    if(c1 + (c12 & 1) > c2) {
        cout << "Alice\n";
    } else {
        cout << "Bob\n";
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
