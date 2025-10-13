#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int get(int L, int R) {
    return rng() % (R - L + 1) + L;
}


void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    vector<int> val(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        val[i] = a[i];
    }

    sort(val.begin() + 1, val.end());
    val.erase(unique(val.begin() + 1, val.end()), val.end());

    int m = val.size();
    vector<vector<int>> mp(m);
    for(int i = 1; i <= n; i++) {
        auto it = lower_bound(val.begin() + 1, val.end(), a[i]) - val.begin();
        mp[it].push_back(i);
    }

    while(q--) {
        int l, r;
        cin >> l >> r;
        set<int> st;
        for(int t = 0; t < 50; t++) {
            int i = get(l, r);
            int x = a[i];
            auto it = lower_bound(val.begin() + 1, val.end(), x) - val.begin();
            auto &vec = mp[it];
            int cnt = upper_bound(vec.begin(), vec.end(), r) - lower_bound(vec.begin(), vec.end(), l);
            if(cnt > (r - l + 1) / 3) {
                st.insert(x);
            }
            if(st.size() >= 2) break;
        }
        if(st.empty()) {
            cout << -1 << "\n";
            continue;
        }
        for(int x : st) {
            cout << x << " ";
        }
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
