#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    ll x, c;
};
void solve() {
    int q;
    cin >> q;
    vector<info> a(q + 1);
    int top = 0, l = 1;
    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int c, x;
            cin >> c >> x;
            a[++top].x = x;
            a[top].c = c;
        } else {
            int k;
            cin >> k;
            ll sum = 0;
            while(l <= top && k) {
                if(a[l].c <= k) {
                    sum += a[l].c * a[l].x;
                    k -= a[l].c;
                    l++;
                } else {
                    sum += k * a[l].x;
                    a[l].c -= k;
                    k = 0;
                }
            }
            cout << sum << "\n";
        }
    }
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
