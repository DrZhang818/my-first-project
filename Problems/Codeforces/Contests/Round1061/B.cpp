#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    bool tag = s.find('B') != string::npos;
    if(!tag) {
        while(q--) {
            int a;
            cin >> a;
            cout << a << "\n";
        }
    } else {
        while(q--) {
            int a;
            cin >> a;
            int cur = 0, ans = 0;
            while(a) {
                ans++;
                if(s[cur] == 'A') {
                    a--;
                } else {
                    a /= 2;
                }
                cur = cur + 1 == n ? 0 : cur + 1;
            }
            cout << ans << "\n";
        }
    }
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
    