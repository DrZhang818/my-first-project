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
    s = "#" + s;
    vector<bool> suf_tag(n + 1);
    int cnt = 1, r = n;
    while(s[r - 1] == s[r]) r--, cnt++;
    if(cnt > k) {
        cout << -1 << "\n";
        return;
    }
    if(cnt == n) {
        cout << n << "\n";
        return;
    }
    for(int r = n - cnt, c = 0, tag = s[r] - '0'; r >= 1; r--) {
        if(s[r] - '0' != tag) {
            if(c < k) break;
            tag ^= 1;
            c = 0;
        }
        c++;
        if(c == k) {
            suf_tag[r] = true;
        } else if(c > k) {
            break;
        }
    }    
    int rem = k - cnt;
    if(rem == 0 && suf_tag[1]) {
        cout << n << "\n";
        return;
    }
    for(int i = 1, c = 0, tag = s[1] - '0'; i <= n - cnt; i++) {
        if(s[i] - '0' != tag) {
            if(c < k) break;
            tag ^= 1;
            c = 0;
        }
        c++;
        if(suf_tag[i + 1] && ((s[i] == s[n] && c == rem) || (rem == 0 && c == k && s[i] != s[n]))) {
            cout << i << "\n";
            return;
        }
        if(c > k) {
            break;
        }
    }
    cout << -1 << "\n";
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
