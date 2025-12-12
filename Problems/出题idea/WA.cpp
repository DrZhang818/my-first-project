#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
array<int,8> power3;

void solve() {
    int k;
    cin >> k;
    vector a(power3[k] + 1, vector<char>(power3[k] + 1, '.'));
    for(int i = 1; i <= power3[k]; i++) {
        for(int j = 1; j <= power3[k]; j++) {
            cout << '#';
        }
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    power3[0] = 1;
    for(int i = 1; i <= 7; i++) {
        power3[i] = power3[i - 1] * 3;
    }

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
