#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    ll a, b, id;
    friend bool operator < (const info &x, const info &y) {
        if(x.a * (y.a + y.b) != y.a * (x.a + x.b)) {
            return x.a * (y.a + y.b) > y.a * (x.a + x.b);
        }
        return x.id < y.id;
    }   
};
void solve() {
    int n;
    cin >> n;
    vector<info> c(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> c[i].a >> c[i].b;
        c[i].id = i;
    }
    sort(c.begin() + 1, c.end());
    for(int i = 1; i <= n; i++) {
        cout << c[i].id << " \n"[i == n];
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
