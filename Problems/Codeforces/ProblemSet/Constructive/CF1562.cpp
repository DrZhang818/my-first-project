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
    int idx = -1;
    for(int i = 0; i < n; i++) {
        if(s[i] == '0') {
            idx = i + 1;
            break;
        }
    }
    if(idx == -1) {
        cout << 1 << " " << n / 2 << " " << n - n / 2 + 1 << " " << n << "\n"; 
    } else if(idx > n / 2) {
        cout << 1 << " " << idx << " " << 1 << " " << idx - 1 << "\n";
    } else {
        cout << idx << " " << n << " " << idx + 1 << " " << n << "\n";
    }
}

int main()0
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
