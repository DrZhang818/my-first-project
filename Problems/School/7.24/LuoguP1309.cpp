#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int s, w, id;
    friend bool operator < (const info &a, const info &b) {
        if(a.s != b.s) return a.s > b.s;
        return a.id < b.id;
    }
};
void solve() {
    int n, r, q;
    cin >> n >> r >> q;
    vector<info> a(2 * n + 1);
    for(int i = 1; i <= 2 * n; i++) {
        cin >> a[i].s;
        a[i].id = i;
    }
    for(int i = 1; i <= 2 * n; i++) {
        cin >> a[i].w;
    }
    while(r--) {
        stable_sort(a.begin() + 1, a.end());
        for(int i = 1; i <= 2 * n; i += 2) {
            if(a[i].w > a[i + 1].w) {
                a[i].s += 1;
            } else {
                a[i + 1].s += 1;
            }
        }
    }
    stable_sort(a.begin() + 1, a.end());
    cout << a[q].id << "\n";
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
