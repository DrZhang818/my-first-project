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
    for(int i = 1; i <= n; i++) {
        if(i == 1) cout << 1 << " " << 1 << "\n";
        else if(i == 2) cout << n << " " << n << "\n";
        else if(i == 3) cout << 2 << " " << 1 << "\n";
        else cout << 1 << " " << i - 1 << "\n";
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
