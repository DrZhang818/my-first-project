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

struct info {
    ll a, b, c;    
};

void solve() {
    int n;
    cin >> n;
    vector<info> vec(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> vec[i].a >> vec[i].b >> vec[i].c; 
    }
    for(int t = 1; t <= 100; t++) {
        ll x = get(0, 1000000);
        bool ok = true;
        for(int i = 1; i <= n; i++) {
            auto [a, b, c] = vec[i];
            if(x * x * x + a * x * x + b * x + c == 0) {
                ok = false;
                break;
            }
        }
        if(ok) {
            cout << x << "\n";
            return;
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
