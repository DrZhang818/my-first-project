#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int a, b;
    cin >> a >> b;
    vector<int> ans;
    bool ok = true;
    for(int i = 0; i < 30; i++) {
        if((a >> i & 1) != (b >> i & 1)) {
            if(a < (1 << i)) {
                ok = false;
                break;
            }
            a ^= 1 << i;
            ans.push_back(1 << i);
        }
    }
    if(!ok) {
        cout << -1 << '\n';
        return;
    }
    assert(a == b);
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " \n"[i == ans.size() - 1];
    }

}   

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
