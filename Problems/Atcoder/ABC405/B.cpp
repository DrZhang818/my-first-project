#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> cnt(m + 1);
    int pos = n;
    for(int i = 1; i <= n; i++) {
        cnt[a[i]]++;
        bool ok = true;
        for(int j = 1; j <= m; j++) {
            if(!cnt[j]) {
                ok = false;
                break;
            }
        }
        if(ok) {
            pos = i - 1;
            break;
        }
    }
    cout << n - pos << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
