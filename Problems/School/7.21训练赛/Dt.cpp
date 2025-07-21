#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
const ull P = 13131;
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = "#" + s;
    vector<map<char,int>> mp(n + 1);
    map<char,bool> vis;
    char ch;
    for(int i = 1; i <= n; i++) {
        mp[i][s[i]]++; 
        vis[s[i]] = true;
        ch = s[i];
        for(char j = 'a'; j <= 'z'; j++) {
            mp[i][j] += mp[i - 1][j];
        }
        for(char j = 'A'; j <= 'Z'; j++) {
            mp[i][j] += mp[i - 1][j];
        }
    }
    int ans = 0;
    unordered_map<ull,int> cnt;
    cnt[0] = 1;
    for(int i = 1; i <= n; i++) {
        int sa = mp[i][ch];
        ull H = 0;
        for(auto [cur, c] : mp[i]) {
            if(vis[cur]) {
                H = H * P + c - sa;
            }
        }
        add(ans, cnt[H]);
        cnt[H]++;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
