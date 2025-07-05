#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    int cur = 0;
    while(q--) {
        int x;
        cin >> x;
        a[x] ^= 1;
        if(n == 1) {
            cur = a[x];
        } else if(x == 1) {
            if(a[x] && !a[x + 1]) {
                cur++;
            } else if(!a[x] && !a[x + 1]) {
                cur--;
            }
        } else if(x == n) {
            if(a[x] && !a[x - 1]) {
                cur++;
            } else if(!a[x] && !a[x - 1]) {
                cur--;
            }
        } else if(a[x - 1] != a[x] && a[x + 1] != a[x]) {
            cur++;
        } else if(a[x - 1] == a[x] && a[x + 1] == a[x]) {
            cur--;
        }
        cout << cur << "\n";
    }
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
