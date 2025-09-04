#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    if(count(s.begin(), s.end(), 'B') != count(t.begin(), t.end(), 'B')) {
        cout << -1 << "\n";
        return;
    }
    if(s == t) {
        cout << 0 << "\n";
        return;
    }
    s += '.';
    s += '.';
    t += '.';
    t += '.';
    unordered_map<string,int> mp;
    mp[s] = 0;
    queue<string> q;
    q.push(s);
    int ans = inf;
    while(!q.empty()) {
        auto cur = q.front(); q.pop();
        int dis = mp[cur];
        int x = find(cur.begin(), cur.end(), '.') - cur.begin();
        for(int i = 0; i < n + 1; i++) {
            if(i == x || i + 1 == x || i == x + 1) continue;
            swap(cur[i], cur[x]);
            swap(cur[i + 1], cur[x + 1]);
            if(!mp.contains(cur)) {
                q.push(cur);
                mp[cur] = dis + 1;
                if(cur == t) {
                    ans = dis + 1;
                    break;
                }
            }
            swap(cur[i], cur[x]);
            swap(cur[i + 1], cur[x + 1]);
        }
        if(ans != inf) {
            break;
        }
    }
    if(ans == inf) {
        cout << -1 << "\n";
        return;
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
