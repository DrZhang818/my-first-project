#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a{k};
    for(int i = 1; i <= n; i++) {
        vector<int> nxt;
        for(int x : a) {
            nxt.push_back(x / 2);
            nxt.push_back((x + 1) / 2);
        }
        swap(a, nxt);
    }
    cout << (k % (1 << n) != 0) << "\n";
    for(int i = 0; i < 1 << n; i++) {
        cout << a[i] << " \n"[i == (1 << n) - 1];
    }
}


// void solve() {
//     int n, k;
//     cin >> n >> k;
//     vector<int> id(1 << n + 1);
//     id[1] = 1;
//     for(int i = 1, dep = 0; i <= (1 << n) - 1; i++) {
//         id[i << 1] = id[i];
//         id[i << 1 | 1] = id[i] + (1 << dep);
//         if(i == (1 << dep + 1) - 1) {
//             dep++;
//         }
//     }
//     vector<int> rid((1 << n) + 1);
//     for(int i = 0; i < 1 << n; i++) {
//         rid[i + 1] = id[(1 << n) + i];
//     }
//     int rem = k % (1 << n);
//     int a = k / (1 << n);
//     cout << (rem != 0) << "\n";
//     for(int i = 1; i <= 1 << n; i++) {
//         if(rid[i] <= rem) {
//             cout << a + 1 << " ";
//         } else {
//             cout << a << " ";
//         }
//     }
//     cout << "\n";
// }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
