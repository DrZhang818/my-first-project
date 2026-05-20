#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    if(n == 1) {
        cout << "FZU\n";
    } else if(n == 2) {
        cout << "FNU\n";
    } else if(n == 3) {
        cout << "FZU\n";
    } else if(n == 4) {
        cout << "FZU\n";
    } else if(n == 5) {
        cout << "FAFU\n";
    } else if(n == 6) {
        cout << "HQU\n";
    } else if(n == 7) {
        cout << "MJU\n";
    } else if(n == 8) {
        cout << "XMUT\n";
    } else if(n == 9) {
        cout << "QNU\n";
    } else if(n == 10) {
        cout << "JMU\n";
    } else {
        cout << "FZU\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}