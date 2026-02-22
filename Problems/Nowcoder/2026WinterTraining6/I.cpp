#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

constexpr int a[12] = {1, 2, 4, 5, 8, 10, 7, 12, 9, 11, 3, 6};

int b[24][24] = {
    {0}, {0}, {0}, {0}, {0}, {0},
    {3,1,6,4,2,5},
    {1,2,4,7,6,3,5},
    {1,3,6,5,4,2,7,8},
    {7,6,2,1,8,4,3,9,5},
    {5,6,9,3,10,2,7,8,4,1},
    {7,4,2,1,10,8,5,6,9,11,3},
    {10,5,8,4,2,7,6,9,1,12,3,11},
    {1,3,9,13,6,4,5,8,2,11,10,12,7},
    {9,11,3,6,1,8,12,5,14,4,13,10,2,7},
    {5,9,15,7,12,8,10,11,2,14,13,4,6,1,3},
    {9,5,3,12,7,15,6,11,16,2,10,4,1,8,14,13},
    {13,3,15,1,12,9,6,17,2,16,7,10,4,11,14,8,5},
    {11,10,12,5,4,6,17,15,9,1,3,18,8,13,14,2,16,7},
    {19,4,8,7,16,14,5,2,10,11,12,15,17,9,3,1,6,18,13},
    {11,6,15,17,3,9,19,18,12,13,4,8,1,14,20,7,10,16,2,5},
    {1,2,4,10,16,17,8,20,19,18,14,7,12,3,5,6,21,13,15,9,11},
    {22,5,16,10,8,19,12,9,1,3,21,11,15,6,13,18,14,20,17,2,4,7},
    {5,9,3,19,15,6,7,22,2,1,10,16,8,13,4,12,23,14,20,17,18,21,11}
};

mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void solve() {  
    int n;
    cin >> n;

    if(n == 3 || n == 5) {
        cout << -1 << "\n";
        return;
    }
    if(n == 4) {
        cout << "3 4 2 1\n";
        return;
    }

    int len = 12 + (n % 12);
    int bias = 0;
    int B = (n - len) / 12;
    
    if(n <= 23) {
        len = n;
    }

    for(int i = 0; i < B; i++) {
        for(int j = 0; j < 12; j++) {
            cout << a[j] + bias << " ";
        }
        bias += 12;
    }

    for(int i = 0; i < len; i++) {
        cout << b[len][i] + bias << " ";
    }
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

    // auto work = [&]() {
    //     vector<int> p(len + 1);
    //     p[0] = las;
    //     iota(p.begin() + 1, p.end(), 1);

    //     for(int t = 0; ; t++) {
    //         shuffle(p.begin() + 1, p.end(), rng);
    //         bool ok = true;
    //         for(int i = 1; i < len; i++) {
    //             int x = p[i - 1], y = p[i], z = p[i + 1];
    //             int c2 = 0, c3 = 0;
    //             for(int r : {x, y, z}) {
    //                 if(r % 2 == 0) c2++;
    //                 if(r % 3 == 0) c3++;
    //             }
    //             if(c2 >= 2 || c3 >= 2) {
    //                 continue;
    //             } else {
    //                 ok = false;
    //                 break;
    //             }
    //         }
    //         if(ok) {
    //             for(int i = 1; i <= len; i++) {
    //                 cerr << p[i] + bias;
    //                 if(i < len) cerr << ",";
    //             }
    //             return;
    //         }
    //     }
    // };