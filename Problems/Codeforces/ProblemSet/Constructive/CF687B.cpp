#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 1000000;

void solve() {  
    int n, k;
    cin >> n >> k;
    ll rem = 1;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        rem = lcm(rem, x) % k;
    }
    if(rem == 0) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
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
