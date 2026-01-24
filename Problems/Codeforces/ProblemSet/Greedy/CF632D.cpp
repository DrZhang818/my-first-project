#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<int> cnt(m + 1);
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(a[i] > m) continue;
        cnt[a[i]]++;
    }
    vector<int> f(m + 1);
    for(int i = 1; i <= m; i++) {
        for(int j = i; j <= m; j += i) {
            f[j] += cnt[i];
        }
    }
    int val = max_element(f.begin(), f.end()) - f.begin();
    int len = f[val];
    if(len == 0) {
        cout << 1 << " " << 0 << "\n";
        return;
    }
    cout << val << " " << len << "\n";
    for(int i = 1; i <= n; i++) {
        if(val % a[i] == 0) {
            cout << i << " ";
        }
    }
    cout << "\n";
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
