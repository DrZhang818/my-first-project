#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    ll ans = 0;
    int xa = 0, bx = 0, ba = 0;
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for(int j = 1; j < s.size(); j++) {
            if(s[j - 1] == 'A' && s[j] == 'B') {
                ans++;
            }
        }
        if(s[0] != 'B' && s.back() == 'A') {
            xa++;
        } else if(s[0] == 'B' && s.back() != 'A') {
            bx++;
        } else if(s[0] == 'B' && s.back() == 'A') {
            ba++;
        }
    }
    if(ba > 0) {
        ans += ba - 1;
        if(xa) ans++,xa--;
        if(bx) ans++,bx--;
    } 
    ans += min(xa, bx);
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
