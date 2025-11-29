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
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    vector<int> v(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        for(int d : fac[a[i]]) {
            if(a[i] > 4 * d - 1) {
                continue;
            } else {
                v[d]++;
            }
        }
    }
    sort(a.begin() + 1, a.end());
    for(int i = n; i >= 2; i--) {
        int cnt = upper_bound(a.begin() + 1, a.end(), 4 * i - 1) - a.begin() - 1;
        cnt -= v[i];
        if(cnt <= k) {
            cout << i << "\n";
            return;
        }
    }
    cout << 1 << "\n";
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
    