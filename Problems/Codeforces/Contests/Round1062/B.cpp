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
    vector<int> cnt(26);
    string s, t;
    cin >> s >> t;
    for(char c : s) {
        cnt[c - 'a']++;
    }
    for(char c : t) {
        cnt[c - 'a']--;
    }
    for(int i = 0; i < 26; i++) {
        if(cnt[i]) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
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
