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
    int ans = 0;
    if(s[0] == 'u') {
        ans++;
        s[0] = 's';
    }
    if(s.back() == 'u') {
        ans++;
        s[n - 1] = 's';
    }
    int c = 0;
    for(int i = 1; i < n; i++) {
        if(s[i] == 'u') {
            c++;
        } else {
            ans += c / 2;
            c = 0;
        }
    }
    cout << ans << "\n";
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
