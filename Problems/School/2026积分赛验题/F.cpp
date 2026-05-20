#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, m;
    cin >> n >> m;
    
    vector<int> cnt(m + 1), visx(m + 1);

    for(int i = 1; i <= n; i++) {
        int l;
        cin >> l;
        for(int j = 1; j <= l; j++) {
            int x;
            cin >> x;
            cnt[x]++;
            visx[x] = i;
        }
    }
    
    vector<int> visy(n + 1);
    for(int i = 1; i <= m; i++) {
        if(cnt[i] == 0) {
            cout << "NO\n";
            return;
        }
        if(cnt[i] == 1) {
            visy[visx[i]] = 1;
        }
    }

    int c = 0;
    for(int i = 1; i <= n; i++) {
        if(!visy[i]) {
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
