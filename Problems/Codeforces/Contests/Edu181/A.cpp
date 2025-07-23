#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    string s;
    cin >> s;
    vector<int> cnt(26);
    for(char c : s) {
        cnt[c - 'A']++;
    }
    for(int i = 0; i < cnt['T' - 'A']; i++) {
        cout << "T";
    }
    for(int i = 0; i < 26; i++) {
        if('A' + i == 'T') continue;        
        while(cnt[i]) {
            cout << char('A' + i);
            cnt[i]--;
        }
    }
    cout << "\n";
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
