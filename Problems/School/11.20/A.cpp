#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int N, K;
    cin >> N >> K;
    vector<array<int,3>> ans;
    vector<int> vis(N);
    set<int> st;
    for(int i = K + 2 * N; i < K + 3 * N; i++) {
        st.insert(i);
    }
    int y = K + N;
    for(int x = K + N - 1; x >= K; x -= 2) {
        if(*st.begin() > K + 2 * N) {
            break;
        }
        auto it = st.lower_bound(x + y);
        if(it == st.end()) {
            cout << -1 << "\n";
            return;
        }
        vis[x - K] = 1;
        ans.push_back({x, y, *it});
        st.erase(it);
        y++;
    }
    for(int x = K + N - 1; x >= K; x--) {
        if(vis[x - K]) continue;
        auto it = st.lower_bound(x + y);
        if(it == st.end()) {
            cout << -1 << "\n";
            return;
        }
        ans.push_back({x, y, *it});
        st.erase(it);
        y++;
    }
    for(auto [x, y, z] : ans) {
        cout << x << " " << y << " " << z << "\n";
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
