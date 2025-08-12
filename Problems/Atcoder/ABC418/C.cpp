#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int N = 1000000;
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> cnt(N + 1);
    ll sum = 0, c = n;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    vector<ll> ans(N + 1, 1);
    for(int b = 1; b <= N; b++) {
        if(c == 0) {
            ans[b] = -1;
            continue;
        }
        ans[b] += sum + (b - 1) * c;
        c -= cnt[b];
        sum += 1LL * b * cnt[b]; 
    }   
    while(q--) {
        int b;
        cin >> b;
        cout << ans[b] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
