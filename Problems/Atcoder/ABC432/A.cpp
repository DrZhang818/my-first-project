#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    array<int,3> a;
    for(int i = 0; i < 3; i++) cin >> a[i];
    sort(a.begin(), a.end(), greater<int>());
    for(int i = 0; i < 3; i++) cout << a[i];
    cout << "\n";
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
