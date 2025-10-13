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
    string sn = to_string(n);
    int len = sn.size();
    while(sn.size() <= 8) {
        sn += sn;
    }
    vector<PII> ans;        
    for(int a = 1; a <= 10000; a++) {
        for(int b = a * len - 8; b <= a * len - 1; b++) {
            if(1 <= b && b <= 10000) {
                int x = stoi(sn.substr(0, a * len - b));
                if(x == n * a - b) {
                    ans.emplace_back(a, b);
                }
            }
        }
    }
    cout << ans.size() << "\n";
    for(auto &[a, b] : ans) {
        cout << a << " " << b << "\n";
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
