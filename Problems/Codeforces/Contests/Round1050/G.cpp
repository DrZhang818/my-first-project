#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int N = 200000;

vector<int> fac[N + 1];

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int mx = ranges::max(a);
    vector<int> cnt(mx + 1);
    vector<int> t;
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int x = a[i];
        vector<int> nt;
        for(int p : fac[x]) {
            cnt[p]++;
            if(cnt[p] == i) {
                nt.push_back(p);
            } else {
                ans = max(ans, cnt[p]);
            }
        }
        for(int y : t) {
            if(cnt[y] != i) {
                ans = i - 1;
                break;
            }
        }
        swap(t, nt);
        cout << ans << " \n"[i == n];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 1; i <= N; i++) {
        for(int j = i; j <= N; j += i) {
            fac[j].push_back(i);
        }
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
