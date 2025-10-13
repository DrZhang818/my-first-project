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
    vector<int> a(n + 1, 1);
    int l = 1, r = n, cnt = 0;
    for(int i = 1; i <= k; i++) {
        if(s[i] == '0') {
            a[l] = 0;
            l++;
        } else if(s[i] == '1') {
            a[r] = 0;
            r--;
        } else {
            cnt++;
        }
    }

    if(r - l + 1 == cnt) {
        for(int i = l; i <= r; i++) {
            a[i] = 0;
        }
    } else {
        for(int i = l; i < l + cnt; i++) {
            a[i] = 2;
        }
        for(int i = r; i > r - cnt; i--) {
            a[i] = 2;
        }
    }

    for(int i = 1; i <= n; i++) {
        if(a[i] == 0) {
            cout << "-";
        } else if(a[i] == 1) {
            cout << "+";
        } else {
            cout << "?";
        }
    }
    cout << "\n";
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
