#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, a, b;
    cin >> n >> a >> b;
    int s;
    cin >> s;
    vector<vector<PII>> adj(n);
    for(int i = 1; i <= s; i++) {
        int t;
        char p;
        string v;
        cin >> t >> p >> v;
        int state;
        if(v[0] == 'a') state = 1;
        else if(v[0] == 'r') state = 2;
        else state = 3;
        adj[p - 'A'].emplace_back(t, state);
    }
    vector<int> vis(n);
    vector<ll> ac(n);
    vector<ll> penalty(n);
    ll cur = 0, cur_cnt = 0, mx_cnt = 0;
    for(int i = 0; i < n; i++) {
        for(auto [t, state] : adj[i]) {
            if(t < 240) {
                if(state == 2) {
                    penalty[i] += 20;
                } else {
                    vis[i] = true;
                    cur += t + penalty[i];
                    cur_cnt++;
                    mx_cnt++;
                    break;
                }
            } else {
                ac[i] = t;
                mx_cnt++;
                break;
            }
        }
    }
    if(cur_cnt > a) {
        cout << 0 << "\n";
        return;
    }
    if(mx_cnt < a) {
        cout << -1 << "\n";
        return;
    }
    int need = a - cur_cnt;
    vector<ll> val;
    for(int i = 0; i < n; i++) {
        if(vis[i]) continue;
        if(ac[i]) {
            val.push_back(penalty[i] + ac[i]);
        }
    }
    sort(val.begin(), val.end());
    for(int i = 0; i < need; i++) {
        cur += val[i];
    }
    if(cur < b) {
        cout << need << "\n";
    } else if(mx_cnt > a) {
        cout << need + 1 << "\n";
    } else {
        cout << -1 << "\n";
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
