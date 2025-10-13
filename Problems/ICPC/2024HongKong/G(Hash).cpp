#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const ull P = 13131;

vector<vector<int>> fac;
void init(int n) {
    fac.resize(n + 1);
    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n;  j += i) {
            fac[j].push_back(i);
        }
    }
}

void solve() {
    int n;
    cin >> n;
    unordered_map<ull,int> mp;
    ll ans = 0;
    vector<int> w(n + 1);
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        ull H = 0;
        for(char c : s) {
            H = H * P + c;
            mp[H]++;
            int cnt = mp[H];
            for(int x : fac[cnt]) {
                ans ^= 1LL * w[x] * x;
                w[x]++;
                ans ^= 1LL * w[x] * x;
            }
        }
        cout << ans << " \n"[i == n];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    init(500000);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
