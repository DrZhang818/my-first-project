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
    vector<int> cnt(m + 1), id(m + 1);
    for(int i = 1; i <= n; i++) {
        int sz;
        cin >> sz;
        for(int j = 1; j <= sz; j++) {
            int x;
            cin >> x;
            cnt[x]++;
            id[x] = i;
        }
    }
    vector<bool> must(n + 1);
    for(int i = 1; i <= m; i++) {
        if(cnt[i] == 0) {
            cout << "NO\n";
            return;
        } else if(cnt[i] == 1) {
            must[id[i]] = true;
        }
    }
    int c = 0;
    for(int i = 1; i <= n; i++) {
        if(!must[i]) {
            c++;
        }
    }
    if(c >= 2) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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
