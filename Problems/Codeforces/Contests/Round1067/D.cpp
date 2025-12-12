#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

vector<vector<int>> pre;

void init() {
    pre.assign(1 << 4, vector<int>(1 << 4, -1));
    for(int S = 0; S < 1 << 4; S++) {
        pre[S][S] = S;
        queue<int> q;
        q.push(S);
        while(!q.empty()) {
            int s = q.front(); q.pop();
            for(int l = 0; l < 4; l++) {
                for(int r = l + 1; r < 4; r++) {
                    string cur;
                    for(int i = l; i <= r; i++) {
                        cur += '0' + (s >> i & 1);
                    }
                    string inv = cur;
                    reverse(inv.begin(), inv.end());
                    if(cur == inv) {
                        int t = s;
                        for(int i = l; i <= r; i++) {
                            t ^= 1 << i;
                        }
                        if(pre[S][t] != -1) {
                            continue;
                        }
                        pre[S][t] = s;
                        q.push(t);
                    }
                }
            }
        }
    }
}

void solve() {
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    vector<array<int,2>> ans;

    int l = 0, r = n - 1;
    for(; l < n - 4; l++) {
        if(s[l] != t[l]) {
            if(s[l] == s[l + 1]) {
                ans.push_back({l, l + 1});
                s[l] ^= 1;
                s[l + 1] ^= 1;
            } else if(s[l] == s[l + 2]) {
                ans.push_back({l, l + 2});
                s[l] ^= 1;
                s[l + 1] ^= 1;
                s[l + 2] ^= 1;
            } else {
                ans.push_back({l + 1, l + 2});
                ans.push_back({l, l + 2});
                s[l] ^= 1;
            }
        }
    }
    int S = 0, T = 0;
    for(int i = l; i <= r; i++) {
        S |= (s[i] == '1') << (r - i);
        T |= (t[i] == '1') << (r - i);
    }
    while(S != T) {
        int nS = pre[T][S];
        int L = l, R = r;
        for(int i = 3; i >= 0; i--) {
            if((nS >> i & 1) == (S >> i & 1)) {
                L++;
            } else {
                break;
            }
        }
        for(int i = 0; i < 4; i++) {
            if((nS >> i & 1) == (S >> i & 1)) {
                R--;
            } else {
                break;
            }
        }
        ans.push_back({L, R});
        S = nS;
    }

    cout << ans.size() << "\n";
    for(auto [l, r] : ans) {
        cout << l + 1 << " " << r + 1 << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    init();

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
