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
    int c0 = 0, c1 = 0;
    for(char c : s) {
        c0 += c == '0';
        c1 += c == '1';
    }
    int t = (n - 2 * k) / 2;
    if(c0 >= t && c1 >= t && (c0 - t) % 2 == 0 && (c1 - t) % 2 == 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
