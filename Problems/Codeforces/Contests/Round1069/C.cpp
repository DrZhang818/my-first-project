#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    string s, t;
    cin >> s >> t;
    array<int,26> cs {}, ct {};
    for(char c : s) {
        cs[c - 'a']++;
    }
    for(char c : t) {
        ct[c - 'a']++;
    }
    for(int i = 0; i < 26; i++) {
        if(ct[i] < cs[i]) {
            cout << "Impossible" << "\n";
            return;
        }
    }
    int p = 0;
    for(int i = 0; i < t.size(); i++) {
        for(int j = 0; j < 26; j++) {
            if(!ct[j]) continue;
            if(p >= s.size() || j == s[p] - 'a') {
                t[i] = char('a' + j);
                cs[j]--;
                ct[j]--;
                p++;
                break;
            } else if(ct[j] - 1 >= cs[j]) {
                t[i] = char('a' + j);
                ct[j]--;
                break;
            }
        }
    }
    cout << t << "\n";
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
