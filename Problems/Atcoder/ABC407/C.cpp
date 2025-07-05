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
    int n = s.size();
    int ans = n, cur = 0;
    for(int i = n - 1; i >= 0; i--) {
        int x = s[i] - '0';
        while(cur != x) {
            ans++;
            cur = (cur + 1) % 10;
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
