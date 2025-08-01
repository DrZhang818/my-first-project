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
    int ans = 0;
    int cnt = 0;
    for(char c : s) {
        if(c == 'g') {
            if(cnt) {
                cnt--;
                ans++;
            } else {
                cnt++;
            }
        } else {
            if(cnt) {
                cnt--;
            } else {
                cnt++;
                ans--;
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
