#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    string s;
    cin >> s;
    int n = s.size();
    array<int,26> cnt {};
    for(char c : s) {
        cnt[c - 'a']++;
    }

    array<int,1<<6> demand {}; 

    vector<array<int,6>> adj(n);

    int q;
    cin >> q;
    while(q--) {
        int p;
        cin >> p;
        p--;
        string t;
        cin >> t;
        s[p] = '#';
        for(char c : t) {
            adj[p][c - 'a'] = 1;
        }
    }

    for(int i = 0; i < n; i++) {
        if(s[i] == '#') continue;
        for(int j = 0; j < 6; j++) {
            adj[i][j] = 1;
        }
    }

    for(int i = 0; i < n; i++) {
        int cur = 0;
        for(int j = 0; j < 6; j++) {
            cur |= adj[i][j] << j;
        }
        for(int s = cur; s < 1 << 6; s = s + 1 | cur) {
            demand[s]++;
        }
    }

    auto ck = [&]() {
        for(int s = 0; s < 1 << 6; s++) {
            int x = 0, y = demand[s];
            for(int i = 0; i < 6; i++) {
                if(s >> i & 1) {
                    x += cnt[i];
                }
            }
            if(y > x) {
                return false;
            }
        }
        return true;
    };

    if(!ck()) {
        cout << "Impossible\n";
        return;
    }

    string ans(n, ' ');

    for(int i = 0; i < n; i++) {
        int cur = 0;
        for(int j = 0; j < 6; j++) {
            cur |= adj[i][j] << j;
        }
        for(int s = cur; s < 1 << 6; s = s + 1 | cur) {
            demand[s]--;
        }
        for(int j = 0; j < 6; j++) {
            if(adj[i][j] && cnt[j] > 0) {
                cnt[j]--;
                if(ck()) {
                    ans[i] = char('a' + j);
                    break;
                }
                cnt[j]++;
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
