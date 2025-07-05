#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000007;

struct info {
    int t, pos;
};
void solve() {
    int n;
    cin >> n;
    int l = -1, r = inf + 1;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].t >> a[i].pos;
    }
    int cnt = 1;
    for(int i = 2; i <= n; i++) {
        cnt = a[i].t == a[i - 1].t ? cnt + 1 : 1;
        if(cnt > 2) {
            cout << -1 << "\n";
            return;
        }
    }
    auto ck = [&](int x) {
        int p1 = a[1].pos, p2 = -inf, t1 = a[1].t, t2 = 0;
        for(int i = 2; i <= n; i++) {
            if(abs(a[i].pos - p1) <= (a[i].t - t1) * x) {
                p1 = a[i].pos;
                t1 = a[i].t;
            } else if(p2 == -inf) {
                p2 = a[i].pos;
                t2 = a[i].t;
            } else if(abs(a[i].pos - p2) <= (a[i].t - t2) * x) {
                p2 = a[i].pos;
                t2 = a[i].t;
            } else {
                return false;
            }
        }
        return true;
    };
    while(l + 1 < r) {
        int mid = l + (r - l) / 2;
        if(ck(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << r << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
