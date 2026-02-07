#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    vector<int> a(4);
    for(int i = 0; i < 4; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    if(a[0] == 1 && a[1] == 4 && a[2] == 7 && a[3] == 9) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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
