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
    for(int i = 0; i < 26; i++) {
        if(cnt[i] != 0) {
            cout << "NO\n";
            return;
        }
    }
    if(n <= 3) {
        cout << (s == t ? "YES" : "NO") << "\n";
    } else if(n == 4) {
        if(s[1] == t[1] && s[2] == t[2]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    } else if(n == 5) {
        if(s[2] == t[2]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    } else {
        cout << "YES\n";
    }
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
