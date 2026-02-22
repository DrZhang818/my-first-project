#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<int> p(n), a(n);
    for(int i = 0; i < n; i++) {
        cin >> p[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int j = 0;
    for(int i = 0; i < n; i++) {
        while(j < n && p[j] != a[i]) {
            j++;
        }
        if(j >= n) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
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
