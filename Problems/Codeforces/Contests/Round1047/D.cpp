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
    vector<int> b(n + 1);
    vector<int> cnt(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
        cnt[b[i]]++;
    }
    for(int i = 1; i <= n; i++) {
        if(cnt[i] % i != 0) {
            cout << -1 << "\n";
            return;
        }
    }
    vector<int> a(n + 1);
    vector<int> id(n + 1);
    int cur = 1;
    for(int i = 1; i <= n; i++) {
        if(cnt[b[i]] % b[i] == 0) {
            id[b[i]] = cur;
            cur++;
        }
        a[i] = id[b[i]];
        cnt[b[i]]--;
    }
    for(int i = 1; i <= n; i++) {
        cout << a[i] << " \n"[i == n];
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
