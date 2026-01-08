#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    string s;
    cin >> s;
    auto it = s.find("2026");
    if(it != string::npos) {
        cout << 0 << "\n";
        return;
    }
    it = s.find("2025");
    if(it == string::npos) {
        cout << 0 << "\n";
        return;
    }
    cout << 1 << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
