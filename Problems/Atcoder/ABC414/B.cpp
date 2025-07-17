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
    int tot = 0, flag = 1;
    string s;
    for(int i = 1; i <= n; i++) {
        char c;
        ll l;
        cin >> c >> l;
        if(l > 100) {
            flag = 0;
        } else {
            tot += l;
            for(int i = 0; i < l; i++) {
                s += c;
            }
        }
    }
    flag &= tot <= 100;
    if(!flag) {
        cout << "Too Long\n";
        return;
    }
    cout << s << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
