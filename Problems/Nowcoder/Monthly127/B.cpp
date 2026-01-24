#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, k;
    cin >> n >> k;
    vector<int> cnt(n + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        x %= k;
        if(cnt[x]) {
            cnt[x]--;
        } else {
            cnt[x]++;
        }
    }
    for(int i = 0; i <= n; i++) {
        if(cnt[i]) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
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
