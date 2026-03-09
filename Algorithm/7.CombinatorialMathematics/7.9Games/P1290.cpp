#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

auto calc(int x, int y) -> int {
    if(x > y) {
        swap(x, y);
    }
    if(x == y || 2LL * x <= y) {
        return 1;
    }
    return calc(x, y - x) ^ 1;
};

void solve() {  
    int x, y;
    cin >> x >> y;
    if(calc(x, y) == 0) {
        cout << "Ollie wins\n";
    } else {
        cout << "Stan wins\n";
    }
}

// int dp[1000][1000];
// auto get_sg(int x, int y) -> int {
//     if(x < y) {
//         swap(x, y);
//     }
//     if(y == 0) {
//         return 0;
//     }
//     if(dp[x][y] != -1) {
//         return dp[x][y];
//     }

//     int tag = 0;
//     for(int i = y; i <= x; i += y) {
//         if(get_sg(x - i, y) == 0) {
//             tag = 1;
//             break;
//         }
//     }

//     return dp[x][y] = tag;
// };


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // memset(dp, -1, sizeof dp);

    // for(int x = 1; x <= 100; x++) {
    //     for(int y = x; y <= 100; y++) {
    //         int sg = get_sg(x, y);
    //         if(sg == 0) {
    //             cerr << x << " " << y << " gcd: " << gcd(x, y) << "\n";
    //         }
    //     }
    // }
    // return 0;

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
