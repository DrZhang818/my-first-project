#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    ll n, m;
    cin >> n >> m;
    vector<string> s(n + 1);
    array<ll,26> cnt {};
    for(int i = 1; i <= n; i++) {
        cin >> s[i];
        for(char c : s[i]) {
            cnt[c - 'A'] += m;
        }
    }
    for(int i = 1; i <= n; i++) {
        array<ll,26> need {};
        for(char c : s[i]) {
            cnt[c - 'A'] -= m;
            need[c - 'A'] += 1;
        }
        ll k = inf;
        for(int j = 0; j < 26; j++) {
            if(cnt[j] < need[j]) {
                k = -1;
                break;
            }
            if(cnt[j] == 0) {
                continue;
            }
            k = min(k, 1LL * (cnt[j] - need[j]) * m / cnt[j]);
        }
        cout << k << " \n"[i == n];
        for(char c : s[i]) {
            cnt[c - 'A'] += m;
        }
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
