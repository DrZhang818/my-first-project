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
    int ans = 0;
    set<pair<string,string>> st;
    for(int i = 1; i <= n; i++) {
        string s, t;
        cin >> s >> t;
        if(st.contains({s, t})) continue;
        ans++;
        st.insert({s, t});
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
