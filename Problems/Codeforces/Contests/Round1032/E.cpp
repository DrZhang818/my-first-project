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
    int ans = 0, n = s.size();
    for(int i = 0; i < n; i++) {
        if(s[i] == t[i]) {
            ans += 2;
        } else if(s[i] + 1 == t[i]) {
            ans++;
            int c0 = 0, c9 = 0;
            for(int j = i + 1; j < n; j++) {
                if(s[j] == '9') {
                    c9++;
                    if(t[j] == '9') c9++;
                } else {
                    if(s[j] == '8' && t[j] == '9') c9++;
                    break;
                }
            }
            for(int j = i + 1; j < n; j++) {
                if(t[j] == '0') {
                    c0++;
                    if(s[j] == '0') c0++;
                } else {
                    if(s[j] == '1' && t[j] == '0') c0++;
                    break;
                }
            }
            ans += min(c0, c9);
            break;
        } else {
            break;
        }
    }
    cout << ans << "\n";
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
