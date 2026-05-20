#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

struct Info {
    int p, c;
    friend bool operator<(const Info& a, const Info& b) {
        return a.c < b.c;
    }
};

void solve() {
    int n;
    i64 S;
    cin >> n >> S;

    vector<Info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].p >> a[i].c;
    }
    sort(a.begin() + 1, a.end());

    i64 sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += a[i].p;
    }

    i64 ans = 0, t = 0;
    for(int i = 1, j = 1; i <= n; i = j) {
        while(j <= n && a[j].c == a[i].c) {
            j++;
        }
        if(sum >= S) {
            t = a[i].c;
        } else {
            for(int k = i; k < j; k++) {
                ans += 1LL * a[k].p * (a[k].c - t);
            }            
        }
        for(int k = i; k < j; k++) {
            sum -= a[k].p;
        }
    }
    ans += S * t;
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}