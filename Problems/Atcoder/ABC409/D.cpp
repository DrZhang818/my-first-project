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
    string s;
    cin >> s;
    int L = 0, R = 0;
    while(L + 1 < n && s[L + 1] >= s[L]) {
        L++;
    }
    R = L;
    while(R + 1 < n && s[R + 1] <= s[L]) {
        R++;
    }
    for(int i = 0; i < L; i++) {
        cout << s[i];
    }
    for(int i = L + 1; i <= R; i++) {
        cout << s[i];
    }
    cout << s[L];
    for(int i = R + 1; i < n; i++) {
        cout << s[i];
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
