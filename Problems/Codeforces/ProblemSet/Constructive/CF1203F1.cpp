#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/1203/problem/F1

//优化解法
struct info {
    int u, v;
    friend bool operator < (const info &a, const info &b) {
        if(a.v >= 0 && b.v < 0) return 1;
        if(a.v < 0 && b.v >= 0) return 0;
        if(a.v >= 0 && b.v >= 0) return a.u < b.u;
        return a.u + a.v > b.u + b.v;
    }
};
void solve() {
    int n, r;
    cin >> n >> r;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].u >> a[i].v;
    }
    sort(a.begin() + 1, a.end());
    for(int i = 1; i <= n; i++) {
        if(r < a[i].u) {
            cout << "NO\n";
            return;
        }
        r += a[i].v;
    }
    if(r >= 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

//自己的做法
// void solve1() {
//     int n, r;
//     cin >> n >> r;
//     vector<PII> pos, neg;
//     ll tot = r;
//     for(int i = 1; i <= n; i++) {
//         int u, v;
//         cin >> u >> v;
//         tot += v;
//         if(v >= 0) {
//             pos.emplace_back(u, v);
//         } else {
//             neg.emplace_back(u, v);
//         }
//     }
//     if(tot < 0) {
//         cout << "NO\n";
//         return;
//     }
//     sort(pos.begin(), pos.end());
//     for(int i = 0; i < pos.size(); i++) {
//         if(r < pos[i].first) {
//             cout << "NO\n";
//             return;
//         }
//         r += pos[i].second;
//     }
//     sort(neg.begin(), neg.end(), greater<PII>());
//     int p1 = 0, p2 = 1;
//     for(int i = 0; i < neg.size(); i++) {
//         if(r < neg[p1].first) {
//             cout << "NO\n";
//             return;
//         }
//         if(i == neg.size() - 1) {
//             cout << "YES\n";
//             return;
//         }
//         bool ok1 = r + neg[p1].second >= neg[p2].first;
//         bool ok2 = r + neg[p2].second >= neg[p1].first;
//         if(ok1 && ok2) {
//             int t1 = r + neg[p1].second + neg[p1].first - neg[p2].first;
//             int t2 = r + neg[p2].second;
//             if(t1 > t2) {
//                 r += neg[p1].second;
//                 p1 = p2;
//                 p2++;
//             } else {
//                 r += neg[p2].second;
//                 p2++;
//             }
//         } else if(ok1) {
//             r += neg[p1].second;
//             p1 = p2;
//             p2++;
//         } else if(ok2) {
//             r += neg[p2].second;
//             p2++;
//         } else {
//             cout << "NO\n";
//             return;
//         }
//     }  
//     cout << "YES\n";
// }

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
