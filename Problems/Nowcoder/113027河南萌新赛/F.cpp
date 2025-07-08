#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    ll s, x;
    cin >> n >> s >> x;
    ll rem = s - x;
    if(rem < 0) {
        cout << "zetsubou\n";        
        return;
    }
    if(rem == 0) {
        cout << s << " ";
        for(int i = 2; i <= n; i++) {
            cout << 0 << " ";
        }
        cout << "\n";
        return;
    }
    if(n == 1) {
        cout << "zetsubou\n";        
        return;
    }
    if(n == 2) {
        if(rem & 1) {
            cout << "zetsubou\n";
            return;
        }
        ll u, v;
        u = v = (rem >> 1);
        u |= x;
        if(u + v == s && (u ^ v) == x) {
            cout << u << " " << v << "\n";
        } else {
            cout << "zetsubou\n";
        }
        return;
    }
    if(rem % 2 == 0) {
        cout << x << " " << rem / 2 << " " << rem / 2 << " ";
        for(int i = 4; i <= n; i++) {
            cout << 0 << " ";
        }
        cout << "\n";
        return;
    } 
    cout << "zetsubou\n";
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
