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
    vector<int> a(n + 1);
    map<int,int> mp;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        mp[a[i]]++;
    }
    int ans = mp[0];
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(j == i || a[i] == 0 && a[j] == 0) continue;
            vector<int> cur = {a[i], a[j]};  
            mp[a[i]]--;
            mp[a[j]]--;
            while(1) {
                int v = cur[cur.size() - 2] + cur.back();
                if(mp[v] > 0) {
                    cur.push_back(v);
                    mp[v]--;
                } else {
                    break;
                }
            }
            ans = max(ans, (int)cur.size());
            for(int v : cur) {
                mp[v]++;
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
