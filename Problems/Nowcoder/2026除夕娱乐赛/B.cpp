#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    if(n <= 3) {
        cout << -1 << "\n";
        return;
    }
    vector<int> a;
    for(int i = n - (n & 1); i > 4; i -= 2) {
        a.push_back(i);
    }
    for(int i : {3, 1, 4, 2}) {
        a.push_back(i);
    }
    for(int i = 5; i <= n; i += 2) {
        a.push_back(i);
    }

    for(int i = 0; i < n; i++) {
        cout << a[i] << " \n"[i == n - 1];
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
