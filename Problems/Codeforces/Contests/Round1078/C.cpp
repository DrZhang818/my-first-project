#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

constexpr int N = 50000;

vector<int> fac[N + 1];

void solve() {  
    int n, k;
    cin >> n >> k;
    vector<string> s(k + 1);
    for(int i = 1; i <= k; i++) {
        cin >> s[i];
    }

    vector<array<int,26>> vis(n);
    for(int i = 1; i <= k; i++) {
        for(int j = 0; j < n; j++) {
            vis[j][s[i][j] - 'a'] = 1;
        }
    }

    for(int x : fac[n]) {
        string s;
        for(int i = 0; i < x; i++) {
            bool found = false;
            for(int c = 0; c < 26; c++) {
                bool ok = true;
                for(int j = i; j < n; j += x) {
                    if(!vis[j][c]) {
                        ok = false;
                        break;
                    }
                }
                if(ok) {
                    found = true;
                    s += char(c + 'a');
                    break;
                }
            }
            if(!found) {
                break;
            }
        }
        if(s.size() == x) {
            for(int i = 0; i < n / x; i++) {
                cout << s;
            }
            cout << "\n";
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 1; i <= N; i++) {
        for(int j = i; j <= N; j += i) {
            fac[j].push_back(i);
        }
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
