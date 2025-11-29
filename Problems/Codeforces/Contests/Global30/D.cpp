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
    string s, t;
    cin >> s >> t;
    vector<int> L(n), R(n, -1);
    int j = n - 1;
    for(int i = n - 1; i >= 0; i--) {
        if(s[i] != t[j]) {
            continue;
        }
        R[i] = j;
        while(j >= i && t[j] == s[i]) {
            j--;
        }
        L[i] = j + 1;
    }
    int mx = 0;
    for(int i = 0; i < n; i++) {
        mx = max(mx, R[i] - i);
    }
    if(j >= 0 || mx > k) {  
        cout << -1 << "\n";
        return;
    }
    cout << mx << "\n";
    for(int p = 1; p <= mx; p++) {
        string r = s;
        for(int i = n - 1; i >= 0; i--) {
            for(int j = i; j <= i + p && j <= R[i]; j++) {
                r[j] = s[i];
            }
        }
        cout << r << "\n";
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
