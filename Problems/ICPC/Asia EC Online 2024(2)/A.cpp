#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int w;
    string s;
};
void solve() {
    int n, k;
    cin >> n >> k;
    int mn = inf;
    for(int i = 1; i <= k; i++) {
        int x;
        cin >> x;
        mn = min(mn, x);
    }
    vector<info> a(n + 1);
    unordered_map<string, vector<int>> mp;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].w >> a[i].s;
        mp[a[i].s].push_back(a[i].w);
    }
    vector<int> val;
    for(auto &[s, vec] : mp) {
        sort(vec.begin(), vec.end(), greater<int>());
        for(int i = 0; i < vec.size() && i < mn; i++) {
            val.push_back(vec[i]);
        }
    }
    sort(val.begin(), val.end(), greater<int>());
    for(int i = 1; i <= n; i++) {
        auto &vec = mp[a[i].s];
        int m = vec.size();
        int pos = lower_bound(val.begin(), val.end(), a[i].w, greater<int>()) - val.begin() + 1;
        if(m <= mn) {
            cout << pos << "\n";
        } else {
            if(a[i].w >= vec[mn - 1]) {
                cout << pos << "\n";
            } else {
                cout << pos - 1 << "\n";
            }
        }
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
