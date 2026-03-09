#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 100000;

void solve() {  
    i64 a, b;
    cin >> a >> b;

    i64 sum = (2 * a + b - 1) * b / 2;

    vector<i64> divs;
    for(i64 i = 1; i * i <= sum; i++) {
        if(sum % i == 0) {
            divs.push_back(i);
            if(i * i != sum) {
                divs.push_back(sum / i);
            }
        }
    }
    sort(divs.rbegin(), divs.rend());

    for(auto d : divs) {
        if(d == sum) continue;
        for(i64 k = 1; k < b; k++) {
            i64 mn = (2 * a + k - 1) * k / 2;
            i64 mx = (2 * a + 2 * b - k - 1) * k / 2;
            if(mx / d * d >= mn) {
                cout << d << "\n";
                return;
            }
        }
    }

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
