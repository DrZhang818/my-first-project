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
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[i] = abs(x);
    }
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] >= a[1]) {
            cnt++;
        }
    }
    if(cnt >= (n + 1) / 2) {
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
