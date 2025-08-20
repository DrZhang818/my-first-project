#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    string s, t;
    cin >> s >> t;
    for(int ls = 0, rs = 0, lt = 0, rt = 0; ls < s.size() || lt < t.size(); ls = rs + 1, lt = rt + 1) {
        if(ls == s.size() || lt == t.size()) {
            cout << "No\n";
            return;
        }
        while(rs + 1 < s.size() && s[rs + 1] == s[ls]) {
            rs++;
        }
        while(rt + 1 < t.size() && t[rt + 1] == t[lt]) {
            rt++;
        }
        int tag = 0;
        if(rs - ls > rt - lt || rs - ls == 0 && rt - lt != 0) {
            tag = 1;
        }
        if(s[ls] != t[lt] || tag) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
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
