#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const ull P = 13131;
void solve() {
    int n, q;
    cin >> n >> q;
    vector<ull> mi(n + 1);
    mi[0] = 1;
    for(int i = 1; i <= n; i++) {
        mi[i] = mi[i - 1] * P;
    }
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    vector<ull> hasha(n + 1), hashb(n + 1);
    ull H = 0;
    for(int i = 1; i <= n; i++) {
        H += mi[a[i]];
        hasha[i] = H;
    }
    H = 0;
    for(int i = 1; i <= n; i++) {
        H += mi[b[i]];
        hashb[i] = H;
    }
    while(q--) {
        int la, ra, lb, rb;
        cin >> la >> ra >> lb >> rb;
        if(ra - la != rb - lb) {
            cout << "No\n";
            continue;
        }
        if(hasha[ra] - hasha[la - 1] == hashb[rb] - hashb[lb - 1]) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
