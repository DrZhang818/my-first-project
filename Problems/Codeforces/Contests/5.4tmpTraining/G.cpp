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
    vector<int> a(n);
    iota(a.begin(), a.end(), 0);
    int cur = 0;
    for(int i = 0; i < n; i++) {
        cur ^= a[i];
        if(cur == 0 && i + 1 < n) {
            cur ^= a[i];
            swap(a[i], a[i + 1]);
            cur ^= a[i];
        } else if(cur == 0) {
            cout << "impossible\n";
            return ;
        }
    }
    for(int i = 0; i < n; i++) {
        cout << a[i] << " \n"[i == n - 1];
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
