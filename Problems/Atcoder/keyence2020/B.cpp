#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

struct Info {
    int l, r;
    friend bool operator<(const Info& a, const Info& b) {
        return a.r < b.r;
    }
};

void solve() {  
    int n;
    cin >> n;
    vector<Info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        int x, l;
        cin >> x >> l;
        a[i] = {x - l, x + l};
    }
    sort(a.begin() + 1, a.end());

    int ans = n;

    int R = a[1].r;
    for(int i = 2; i <= n; i++) {
        auto [l, r] = a[i];
        if(l < R) {
            ans--;
        } else {
            R = r;
        }
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
