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
    vector<int> vis(1 << n);
    vector<int> p;
    p.reserve(1 << n);    
    for(int i = n; i >= 1; i--) {
        int s = (1 << i) - 1;
        p.push_back(s);
        vis[s] = true;
        for(int t = s; t < 1 << n; t = (t + 1) | s) {
            if(!vis[t]) {
                p.push_back(t);
                vis[t] = true;
            }
        }
    }
    for(int i = 0; i < 1 << n; i++) {
        if(vis[i]) continue;
        p.push_back(i);
    }
    for(int i = 0; i < 1 << n; i++) {
        cout << p[i] << " \n"[i == (1 << n) - 1];
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
