#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    std::vector<int> a(4);
    cin >> a[1] >> a[2] >> a[3];
    sort(a.begin() + 1, a.end());
    cout << a[3] * 10 + a[1] + a[2] << "\n";
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
