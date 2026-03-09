#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int a, b;
    cin >> a >> b;
    if(a > b) { swap(a, b); }

    u64 d = b - a;

    u64 x = 2 * a - d;

    if(x * x <= 5 * d * d && 5 * d * d < (x + 2) * (x + 2)) {
        cout << 0 << "\n";
    } else {
        cout << 1 << "\n";
    }
}

// int sg[500][500];
// int get_sg(int x, int y) {
//     if(x == 0 && y == 0) {
//         return 0;
//     }
//     if(sg[x][y] != -1) {
//         return sg[x][y];
//     }
//     unordered_set<int> st;
//     for(int i = 0; i <= x - 1; i++) {
//         st.insert(get_sg(i, y));
//     }
//     for(int i = 0; i <= y - 1; i++) {
//         st.insert(get_sg(x, i));
//     }
//     for(int i = 1; i <= x && i <= y; i++) {
//         st.insert(get_sg(x - i, y - i));
//     }

//     int mex = 0;
//     while(st.contains(mex)) {
//         mex++;
//     }

//     return sg[x][y] = mex;
// }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // memset(sg, -1, sizeof(sg));

    // for(int s = 0; s <= 500; s++) {
    //     for(int x = 0; x <= 100; x++) {
    //         int y = s - x;
    //         if(y < x) continue;
    //         int sg = get_sg(x, y);
    //         if(sg == 0) {
    //             cerr << x << " " << y << " SG: " << get_sg(x, y) << "\n";
    //         }
    //     }
    // }

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
