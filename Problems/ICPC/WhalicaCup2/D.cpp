#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;
constexpr i64 MOD = i64(1E18) + 9;
constexpr int P = 13131;

char word[] = {'w', 'h', 'a', 'l', 'i', 'c'};
int to[256];

void solve() {  
    int n, q;
    cin >> n >> q;
    vector<string> ss(n + 1);
    int mx = 0;
    for(int i = 1; i <= n; i++) {
        cin >> ss[i];
        mx = max(mx, int(ss[i].size()));
    }

    vector mp(6, vector<unordered_map<i64, i64>>(mx));

    for(int i = 0; i < 6; i++) {
        for(int j = 1; j <= n; j++) {
            string& s = ss[j];
            i64 H = 0;
            for(int k = 0; k < s.size(); k++) {
                int w = (to[s[k]] + i) % 6;
                H = (i128(H) * P + word[w]) % MOD;
                mp[i][k][H]++;
            }
        }
    }

    int tag = 0;

    auto calc = [&](const string& t) -> i64 {
        i64 res = 0;
        i64 H = 0;
        for(int i = 0; i < t.size() && i < mx; i++) {
            int k = to[t[i]];
            H = (i128(H) * P + word[k]) % MOD;
            res += mp[tag][i][H];
        }
        return res;
    };

    while(q--) {
        int op;
        cin >> op;

        if(op == 1) {
            string t;
            cin >> t;
            cout << calc(t) << "\n";
        } else {
            tag = (tag + 1) % 6;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    to['w'] = 0;
    to['h'] = 1;
    to['a'] = 2;
    to['l'] = 3;
    to['i'] = 4;
    to['c'] = 5;

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
