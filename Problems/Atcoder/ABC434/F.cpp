#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr ull P = 13131;
constexpr int N = 1000000;

vector<vector<ull>> Hash;
vector<ull> power(N + 1);

void solve() {
    int n;
    cin >> n;
    vector<string> s(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> s[i];
    }
    if(n == 2) {
        cout << max(s[1] + s[2], s[2] + s[1]) << "\n";
        return;
    }
    Hash.resize(n + 1);
    for(int i = 1; i <= n; i++) {
        int m = s[i].size();
        Hash[i].resize(m + 1);
        for(int j = 1; j <= m; j++) {
            char c = s[i][j - 1];
            Hash[i][j] = Hash[i][j - 1] * P + c;
        }
    }
    auto cmp = [&](int i, int j) -> int {
        int n1 = s[i].size();
        int n2 = s[j].size();
        int l = 0, r = n1 + n2 + 1;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            ull H1 = 0, H2 = 0;
            if(mid <= n1) {
                H1 = Hash[i][mid];
            } else {
                H1 = Hash[j][mid - n1] + Hash[i][n1] * power[mid - n1];
            }
            if(mid <= n2) {
                H2 = Hash[j][mid];
            } else {
                H2 = Hash[i][mid - n2] + Hash[j][n2] * power[mid - n2];
            }
            if(H1 != H2) {
                r = mid;
            } else {
                l = mid;
            }
        }
        if(r == n1 + n2 + 1) return 2;  
        char c1 = r <= n1 ? s[i][r - 1] : s[j][r - n1 - 1];
        char c2 = r <= n2 ? s[j][r - 1] : s[i][r - n2 - 1];
        return c1 < c2;
    };
    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    sort(p.begin() + 1, p.end(), 
        [&](auto x, auto y) {
            return cmp(x, y) == 1;
        });
    bool equal = false;
    for(int i = 1; i < n; i++) {
        if(cmp(p[i], p[i + 1]) == 2) {
            equal = true;
            break;
        }
    }
    if(!equal) {
        for(int i = 1; i < n - 2; i++) {
            cout << s[p[i]];
        }
        string ans1 = s[p[n - 2]] + s[p[n]] + s[p[n - 1]];
        string ans2 = s[p[n - 1]] + s[p[n - 2]] + s[p[n]];
        cout << min(ans1, ans2) << "\n";
    } else {
        for(int i = 1; i <= n; i++) {
            cout << s[p[i]];
        }
        cout << "\n";
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    power[0] = 1;
    for(int i = 1; i <= N; i++) {
        power[i] = power[i - 1] * P;
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
