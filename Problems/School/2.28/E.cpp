#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    string s, t;
    cin >> s >> t;
    vector<int> cnt(26);
    for(char c : s) {
        cnt[c - 'a'] += 1;
    }
    for(char c : t) {
        if(cnt[c - 'a'] == 0) {
            cout << -1 << "\n";
            return;
        }
    }
    vector<vector<int>> to(26);
    for(int i = 0; i < s.size(); i++) {
        int c = s[i] - 'a';
        to[c].push_back(i + 1);
    }
    int cur = 0, n = s.size();
    ll ans = 0;
    for(int i = 0; i < t.size(); i++) {
        int c = t[i] - 'a';
        auto pos = upper_bound(to[c].begin(), to[c].end(), cur);
        if(pos == to[c].end()) {
            ans += n - cur;
            cur = to[c][0];
            ans += cur;
        } else {
            ans += *pos - cur;
            cur = *pos;
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
