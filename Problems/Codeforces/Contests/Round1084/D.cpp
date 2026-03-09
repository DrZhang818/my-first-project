#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> a, b;
    for(int i = 1; i <= n; i++) {
        int v;
        cin >> v;
        if(x < i && i <= y) {
            b.push_back(v);
        } else {
            a.push_back(v);
        }
    }

    rotate(b.begin(), min_element(b.begin(), b.end()), b.end());

    if(a.empty()) {
        a = move(b);
    } else if(!b.empty()) {
        for(int i = 0; i < a.size(); i++) {
            if(a[i] > b[0]) {
                a.insert(a.begin() + i, b.begin(), b.end());
                break;
            }
        }
        if(a.size() != n) {
            a.insert(a.end(), b.begin(), b.end());
        }
    }

    assert(a.size() == n);    
    for(auto v : a) {
        cout << v << " \n"[v == a.back()];
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
