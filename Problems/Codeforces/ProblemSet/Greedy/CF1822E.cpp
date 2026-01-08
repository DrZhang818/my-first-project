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
    string s;
    cin >> s;
    if(n & 1) {
        cout << -1 << "\n";
        return;
    }
    array<int,26> cnt {};
    for(char c : s) {
        cnt[c - 'a']++;
        if(cnt[c - 'a'] > n / 2) {
            cout << -1 << "\n";
            return;
        }
    }
    fill(cnt.begin(), cnt.end(), 0);
    for(int i = 0; i < n / 2; i++) {
        if(s[i] == s[n - 1 - i]) {
            cnt[s[i] - 'a']++;
        }
    }
    int sum = accumulate(cnt.begin(), cnt.end(), 0);
    int mx = *max_element(cnt.begin(), cnt.end());
    if(mx > sum - mx) {
        cout << mx << "\n";
    } else {
        cout << (sum + 1) / 2 << "\n";
    }
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
