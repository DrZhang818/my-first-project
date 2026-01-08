#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000007;

struct Info {
    int x, i, j;
    friend bool operator < (const Info& a, const Info& b) {
        return a.x < b.x;
    };
};

void solve() {  
    int n;
    cin >> n;
    vector<int> x1(n + 1), x2(n + 1);
    vector<vector<int>> L(n + 1), R(n + 1);
    int l = 0, r = inf;
    multiset<int> st;
    vector<Info> line;
    for(int i = 1; i <= n; i++) {
        int k;
        cin >> k >> x1[i] >> x2[i];
        L[i].resize(k + 2);
        R[i].resize(k + 2);
        vector<int> pos(k + 1);
        for(int j = 1; j <= k; j++) {
            cin >> pos[j];
        }
        L[i][0] = x1[i];
        R[i][k + 1] = x2[i];
        st.insert(x2[i]);
        l = max(l, x1[i]);
        for(int j = 1; j <= k; j++) {
            L[i][j] = L[i][j - 1] + pos[j];
            line.push_back({L[i][j], i, j});
        }
        for(int j = k; j >= 1; j--) {
            R[i][j] = R[i][j + 1] - pos[j];
            st.insert(R[i][j]);
        }
    }
    sort(line.begin(), line.end());
    r = min(r, *st.begin());
    int ans = max(0, r - l);
    for(auto [x, i, j] : line) {
        l = max(l, x);
        auto it = st.find(R[i][j]);
        st.erase(it);
        r = *st.begin();
        ans = max(ans, r - l);
    }
    cout << ans << "\n";
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
