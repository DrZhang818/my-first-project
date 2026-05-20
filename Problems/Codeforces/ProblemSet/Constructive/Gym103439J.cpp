#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    string s;
    cin >> n >> s;

    array<int, 3> cnt {};
    for(char c : s) {
        cnt[c - 'A']++;
    }
    vector<pair<int, char>> a {
        {cnt[0], 'A'}, {cnt[1], 'B'}, {cnt[2], 'C'}
    };

    sort(a.begin(), a.end());
    auto [x, chx] = a[0];
    auto [y, chy] = a[1];
    auto [z, chz] = a[2];

    if(x == n && y == n && z == n) {
        cout << 0 << "\n";
        return;
    }

    vector<tuple<int,int,char>> ans;
    if(y >= n) {
        int need = n - x;
        int c1 = y, c2 = z;
        for(int i = 0, j = 0; i < 3 * n; i++) {
            if(s[i] == chy) {
                c1--;
                need--;
            } else if(s[i] == chz) {
                c2--;
                need--;
            }
            if(need == 0 && c1 == n && c2 == n) {
                ans.emplace_back(j + 1, i + 1, chx);
                break;
            }
            while(c1 < n || c2 < n) {
                c1 += s[j] == chy;
                c2 += s[j] == chz;
                need += s[j] != chx;
                j++;
            }
        }
    }
    if(!ans.empty()) {
        cout << 1 << "\n";
        for(auto [l, r, c] : ans) {
            cout << l << " " << r << " " << c << "\n";
        }
        return;
    }

    array<int, 3> c {};
    for(int i = 0; i < 3 * n; i++) {
        for(int j = 0; j < 3; j++) {
            c[j] += s[i] == a[j].second;
            if(c[j] == n) {
                int u = 0, v = 1;
                while(u == j) u++;
                while(v == j || v == u) v++;
                ans.emplace_back(i + 2, 3 * n, a[u].second);
                ans.emplace_back(3 * n - (n - c[v]) + 1, 3 * n, a[v].second);
                break;
            }
        }
        if(!ans.empty()) {
            break;
        }
    }
    cout << 2 << "\n";
    for(auto [l, r, c] : ans) {
        cout << l << " " << r << " " << c << "\n";
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
