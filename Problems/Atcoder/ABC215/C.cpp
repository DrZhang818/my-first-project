#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    string s;
    int k;
    cin >> s >> k;
    sort(s.begin(), s.end());
    while(k > 1) {
        next_permutation(s.begin(), s.end());
        k--;
    }
    cout << s << "\n";
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
