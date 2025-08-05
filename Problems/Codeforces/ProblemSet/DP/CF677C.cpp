#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
int mp[200];
void solve() {
    string s;
    cin >> s;
    int ans = 1;
    for(char c : s) {
        int x = mp[c], cur = 1;
        for(int i = 0; i < 6; i++) {
            if(!(x >> i & 1)) {
                cur = 3LL * cur % MOD;
            }
        }
        ans = 1LL * ans * cur % MOD;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(char c = '0'; c <= '9'; c++) mp[c] = c - '0';
    for(char c = 'A'; c <= 'Z'; c++) mp[c] = c - 'A' + 10;
    for(char c = 'a'; c <= 'z'; c++) mp[c] = c - 'a' + 36;
    mp['-'] = 62;
    mp['_'] = 63;
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
