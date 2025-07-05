#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const ll MX = 1LL << 32;

void solve() {
    int q;
    cin >> q;
    vector<ll> a(q + 1);
    int r = 0;
    vector<int> pre0(q + 1), pre1(q + 1);
    int lst0 = -1, lst1 = -1;
    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            ll x;
            cin >> x;
            a[++r] = x;
            if(x == 0) {
                pre0[r] = lst0;
                lst0 = r;
                lst1 = -1;
            } else if(x == 1) {
                if(lst1 == -1) {
                    lst1 = r;
                }
                pre1[r] = lst1;
            } else {
                lst1 = -1;
            }
        } else if(op == 2) {
            if(r == 0) continue;
            if(a[r] == 0) {
                lst0 = pre0[r];
            } else if(a[r] == 1) {
                if(lst1 == r) {
                    lst1 = -1;
                }
            }
            r--;                
        } else {
            int y;
            cin >> y;
            if(r < y) {
                cout << "ERROR\n";
            } else if(r - lst0 + 1 <= y) {
                cout << 0 << "\n";
            } else {
                ll fac = 1;
                for(int i = r; i > r - y; i--) {
                    if(a[i] == 1) {
                        i = pre1[i];
                    } else {
                        fac *= a[i];
                    }
                    if(fac >= MX) break;
                }
                if(fac >= MX) {
                    cout << "OVERFLOW\n";
                } else {
                    cout << fac << "\n";
                }
            }
        }
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
