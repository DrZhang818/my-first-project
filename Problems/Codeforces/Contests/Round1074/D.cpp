#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m, h;
    cin >> n >> m >> h;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    auto tmp = a;
    vector<int> t(n + 1);
    int timer = 0;
    for(int i = 1; i <= m; i++) {
        int b, c;
        cin >> b >> c;
        if(t[b] != timer) {
            t[b] = timer;
            a[b] = tmp[b];
        }
        a[b] += c;
        if(a[b] > h) {
            timer++;
        }
    }
    for(int i = 1; i <= n; i++) {
        if(t[i] == timer) {
            cout << a[i];
        } else {
            cout << tmp[i];
        }
        cout << " \n"[i == n];
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
