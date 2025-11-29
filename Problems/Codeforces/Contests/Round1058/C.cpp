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
    n = n >> __builtin_ctz(n);
    string s;
    do {
        s += (n & 1) + '0';
        n >>= 1;
    } while(n);
    n = s.size();
    for(int i = 0, j = n - 1; i <= j; i++, j--) {
        if(s[i] != s[j] || i == j && s[i] != '0') {
            cout << "NO\n";
            return;
        }    
    }
    cout << "YES\n";
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
