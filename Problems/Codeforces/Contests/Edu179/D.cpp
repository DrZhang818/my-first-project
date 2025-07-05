#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, m;
    cin >> n >> m;
    map<int,set<int>> mp;
    for(int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        int id = x % 100;
        x /= 100;
        mp[x].insert(id);
    }
    for(int i = 1; i <= n; i++) {
        auto &[u, st1] = *mp.begin();
        auto &[v, st2] = *mp.rbegin();
        int id1 = *st1.begin(), id2 = *st2.rbegin();
        int x = u * 100 + id1, y = v * 100 + id2;
        if(i & 1) {
            for(int j = 1; j <= 6; j++) {
                if(j & 1) {
                    cout << x << " ";
                } else {
                    cout << y << " ";
                }
            }
            cout << "\n";
        } else {
            for(int j = 1; j <= 6; j++) {
                if(j & 1) {
                    cout << y << " ";
                } else {
                    cout << x << " ";
                }
            }
            cout << "\n";
            st1.erase(id1);
            st2.erase(id2);
            if(st1.empty()) mp.erase(u);
            if(st2.empty()) mp.erase(v);
        }
    }
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
