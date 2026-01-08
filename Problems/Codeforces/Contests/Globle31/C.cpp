#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, k;
    cin >> n >> k;
    if(k & 1) {
        for(int i = 1; i <= k; i++) {
            cout << n << " \n"[i == k];
        }
        return;
    }
    vector<int> a(k, n), b {};
    for(int i = __lg(n) + 1; i >= 0; i--) {
        if(n >> i & 1) {
            if(a.empty()) {
                for(int j = 0; j < b.size(); j++) {
                    b[j] |= 1 << i;
                }
                b.back() ^= (1 << i);
            } else {
                a.pop_back();
                for(int &x : b) {
                    x |= 1 << i;
                }
                b.push_back(n ^ (1 << i));
            }
        } else {
            for(int j = 0; j < b.size(); j += 2) {
                if(j + 1 < b.size()) {
                    b[j] |= 1 << i;
                    b[j + 1] |= 1 << i;
                }
            }
        }
    }

    for(int i = 0; i < a.size(); i++) {
        cout << a[i] << " ";
    }
    for(int i = 0; i < b.size(); i++) {
        cout << b[i] << " ";
    }
    cout << "\n";
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
