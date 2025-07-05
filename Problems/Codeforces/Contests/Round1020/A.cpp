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
    ll ans = 0, c0 = 0, c1 = 0;
    for(char c : s) {
        if(c == '0') c0++;
        else c1++;
    }
    cout << n * c1 + c0 - c1 << "\n";
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
