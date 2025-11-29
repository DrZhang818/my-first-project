#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int query(vector<int> &a) {
    cout << "? " << a.size();
    for(int x : a) {
        cout << " " << x;
    }
    cout << endl;
    int res;
    cin >> res;
    return res;
}

void solve() {
    int n;
    cin >> n;
    vector<int> ans(2 * n + 1);
    vector<int> a, b;
    for(int i = 1; i <= 2 * n; i++) {
        a.push_back(i);
        auto x = query(a);
        if(x) {
            a.pop_back();
            b.push_back(i);
            ans[i] = x;            
        }
    }
    for(int i = 1; i <= 2 * n; i++) {
        if(!ans[i]) {
            b.push_back(i);
            ans[i] = query(b);
            b.pop_back();
        }
    }
    cout << "!";
    for(int i = 1; i <= 2 * n; i++) {
        cout << " " << ans[i];
    }
    cout << endl;
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
