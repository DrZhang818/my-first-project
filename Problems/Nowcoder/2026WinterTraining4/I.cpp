#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    cout << "######\n" << "\n";
    // db mx = 0;

    // vector<int> mxcnt(7);
    // vector<int> cnt(7);

    // auto dfs = [&](this auto&& self, int i, int rem) -> void {
    //     if(i == 7) {
    //         if(rem > 0) return;

    //         db cur = 0;

    //         for(int j = 1; j <= 6; j++) {
    //             for(int k = 1; k <= 3; k++) {
    //                 db p = 1;
    //                 for(int t = 0; t < k; t++) {
    //                     p /= 6;
    //                 }
    //                 db c = cnt[j] * p;
    //                 if(k == 1) c *= 2;
    //                 if(k == 2) c *= 3;
    //                 if(k == 3) c *= 10;
    //                 cur += c;
    //             }
    //         }

    //         if(cur > mx) {
    //             mxcnt = cnt;
    //         }
    //         mx = max(mx, cur);
    //         return;
    //     }

    //     int up = rem;
    //     if(i != 1) up = min(up, cnt[i - 1]);

    //     for(int j = 0; j <= up; j++) {
    //         cnt[i] = j;
    //         self(i + 1, rem - j);
    //         cnt[i] = 0;
    //     }
    // };

    // db ans = 0;

    // vector<int> vec;

    // for(int i = 0; i <= 6; i++) {
    //     mx = 0;
    //     dfs(1, i);
    //     db cur = 6 - i + mx;
    //     cerr << "i: " << i << " " << cur << "\n";
    //     if(cur > ans) {
    //         ans = cur;
    //         vec = mxcnt;
    //     }
    // }

    // for(int i = 1; i <= 6; i++) {
    //     cout << vec[i] << " \n"[i == 6];
    // }

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
