#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, k;
    cin >> n >> k;
    string s, t;
    cin >> s >> t;
    vector<int> cnt(26);
    for(char c : s) cnt[c - 'a']++;
    for(char c : t) cnt[c - 'a']--;
    s = "#" + s, t = "#" + t;
    for(int x : cnt) if(x) { cout << "NO\n"; return; }
    for(int i = 1; i + k <= n; i++) {
        s[i] = s[i + k] = t[i] = t[i + k] = '.';
    } 
    for(int i = 1; i <= n; i++) {
        if(s[i] != t[i]) {
            cout << "NO\n";
            return ;
        }
    }
    cout << "YES\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
