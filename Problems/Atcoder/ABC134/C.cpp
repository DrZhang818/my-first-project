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
        cin >> a[i];
    }
    vector<int> vis(n + 1);
    int c = 0;
    for(int i = n; i >= 1; i--) {
        int cnt = 0;
        for(int j = i + i; j <= n; j += i) {
            cnt += vis[j];
        }
        if(cnt % 2 == a[i] % 2) {
            vis[i] = 0;
        } else {
            vis[i] = 1;
            c += 1;
        }
    }
    cout << c << "\n";
    for(int i = 1; i <= n; i++) {
        if(vis[i]) {
            cout << i << " ";
        }
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
