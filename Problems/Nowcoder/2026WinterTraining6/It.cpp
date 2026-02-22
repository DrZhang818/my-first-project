#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    
    int n = 17;
    
    std::vector<int> a(n + 1);
    a[0] = 6;    
    std::iota(a.begin() + 1, a.end(), 1);

    do {
        bool ok = true;
        for(int i = 1; i < n - 1; i++) {
            int x = a[i - 1], y = a[i], z = a[i + 1];
            if(gcd(x, y) == 1 && gcd(x, z) == 1 && gcd(y, z) == 1) {
                ok = false;
                break;
            }
        }
        if(ok) {
            for(auto x : a) {
                cerr << x << ", ";
            }
            cout << "\n";
        }
    } while (next_permutation(a.begin(), a.end()));
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

    //     for(int t = 0; t < 1000000; t++) {
    //         shuffle(p.begin() + 1, p.end(), rng);
    //         bool ok = true;
    //         for(int i = 1; i < len; i++) {
    //             int x = p[i - 1], y = p[i], z = p[i + 1];
    //             if(x != 0 && gcd(x, y) == 1 && gcd(x, z) == 1 && gcd(y, z) == 1) {
    //                 ok = false;
    //                 break;
    //             }
    //         }
    //         if(ok) {
    //             for(int i = 1; i <= len; i++) {
    //                 cout << p[i] + bias << ",";
    //             }
    //             return;
    //         }
    //     }
    // };

    // work();