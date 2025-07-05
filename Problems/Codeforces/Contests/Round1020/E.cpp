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
    vector<int> a(n + 1), pos(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    while(q--) {
        int l, r, x;
        cin >> l >> r >> x;
        if(pos[x] < l || pos[x] > r) {
            cout << -1 << " ";
            continue;
        }
        int op1 = x - 1, op2 = n - x, d = 0, c1 = 0, c2 = 0;
        bool ok = true;
        while(l <= r) {
            int mid = l + r >> 1;
            if(mid == pos[x]) break;
            if(mid > pos[x]) {
                if(op2 <= 0) {
                    ok = false;
                    break;
                }
                op2--;
                if(a[mid] > x) {
                    c1 = min(c1, op2);
                } else {
                    if(c1 == 0) d += 2, c2++;
                    else c1--;
                }
                r = mid - 1;
            } else {
                if(op1 <= 0) {
                    ok = false;
                    break;
                }
                op1--;
                if(a[mid] < x) {
                    c2 = min(c2, op1);
                } else {
                    if(c2 == 0) d += 2, c1++;
                    else c2--;
                }
                l = mid + 1;
            }
        }
        if(!ok) {
            cout << -1 << " ";
        } else {
            cout << d << " ";
        }
    }
    cout << "\n";
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
