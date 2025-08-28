#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    sort(s.begin(), s.end());
    vector<char> a(n);
    vector<char> vis(26);
    bool ok = true;
    for(int i = 0; i < n; i++) {
        a[i] = s[i];
        if(vis[s[i] - 'a']) ok = false;
        vis[s[i] - 'a']++;
    }
    ll ans = 0;
    if(ok) {
        ans = 1;
        for(int i = 1; i <= n; i++) {
            ans *= i;
        }
        cout << ans << "\n";
        return;
    }
    do {
        string t = "$#";
        for(int i = 0; i < n; i++) {
            t += a[i];  
            t += "#";
        }
        t += "&";
        int m = t.size();
        vector<int> P(m);
        int R = 0, C;
        for(int i = 1; i < m - 1; i++) {
            P[i] = i < R ? min(P[2 * C - i], P[C] + C - i) : 1;
            while(t[i + P[i]] == t[i - P[i]]) P[i]++;
            if(P[i] + i > R) R = P[i] + i, C = i;
        }
        bool ok = false;
        for(int i = 0; i < m; i++) {
            if(P[i] - 1 >= k && (P[i] - 1) % 2 == k % 2) {
                ok = true;
            }
        }
        if(!ok) {
            ans++;
        }
    } while(next_permutation(a.begin(), a.end()));
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
