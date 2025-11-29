#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> a(n + 1);
    for(int i = 0; i < n; i++) {
        a[i + 1] = s[i] - '0';
    }
    int ans = 0;
    for(int i = 2, j = 1; i <= n; i++) {
        if(a[i - 1] != a[i]) {
            j = i - 1;
        }
        if(a[j] + 1 == a[i]) {
            ans++;
            j--;
            if(j == 0) {
                j = i;
            }
        } else {
            j = i;
        }
    }
    cout << ans << "\n";
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
