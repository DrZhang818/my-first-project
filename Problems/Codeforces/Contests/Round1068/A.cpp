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
    string s;
    cin >> s;
    int ans = 0;
    for(int i = 0, rem = 0; i < n; i++) {
        if(s[i] == '1') {
            rem = k;
        } else {
            if(rem) {
                rem--;
            } else {
                ans++;
            }
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
