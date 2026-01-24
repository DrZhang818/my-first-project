#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n = 15;
    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    do {
        bool ok = true;
        for(int i = 1; i <= n; i++) {
            int x = p[i] ^ i;
            bool found = false;
            for(int j = i; j <= n; j++) {
                if(p[j] == x) {
                    found = true;
                    break;
                }
            }
            if(!found) {
                ok = false;
                break;
            }
        }
        if(ok) {
            for(int i = 1; i <= n; i++) {
                cerr << p[i] << " \n"[i == n];
            }
        }
    } while (next_permutation(p.begin() + 1, p.end()));
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
