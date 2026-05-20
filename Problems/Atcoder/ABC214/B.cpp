#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int S, T;
    cin >> S >> T;
    i64 ans = 0;
    for(int a = 0; a <= S; a++) {
        for(int b = 0; a + b <= S; b++) {
            for(int c = 0; a + b + c <= S; c++) {
                if(a * b * c <= T) {
                    ans++;
                }
            }
        }
    }
    cout << ans << "\n";
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
