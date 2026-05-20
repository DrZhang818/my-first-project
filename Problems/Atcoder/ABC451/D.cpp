#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

vector<int> vec;
vector<int> sz;
vector<int> pw10(10);
auto init = []() {
    for(int i = 0; i < 31; i++) {
        vec.push_back(1 << i);
        sz.push_back(to_string(1 << i).size());
    }
    pw10[0] = 1;
    for(int i = 1; i < 10; i++) {
        pw10[i] = pw10[i - 1] * 10;
    }
    return 1;
}();

void solve() {
    vector<int> a;
    [&](this auto&& self, int cur, int len) -> void {
        if(cur != 0) {
            a.push_back(cur);
        }
        for(int i = 0; i < vec.size(); i++) {
            if(len + sz[i] > 9) break;
            int nxt = cur * pw10[sz[i]] + vec[i];
            int nlen = len + sz[i];
            self(nxt, nlen);
        }
    }(0, 0);

    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    
    int n;
    cin >> n;
    cout << a[n - 1] << "\n";
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
