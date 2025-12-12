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
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        a[i] = c - '0';
    }
    rotate(a.begin() + 1, find(a.begin() + 1, a.end(), 1), a.end());
    int mx = 0;
    for(int i = 1, j = i + 1; i <= n; i = j, j++) {
        while(j <= n && a[j] == 0) {
            j++;
        }
        mx = max(mx, j - i - 1);
    }
    cout << mx << "\n";
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
