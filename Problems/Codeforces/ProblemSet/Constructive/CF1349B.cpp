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
    vector<int> pos;
    bool found = false;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if(x >= k) {
            pos.push_back(i);
        }
        if(x == k) {
            found = true;
        }
    }
    if(!found) {
        cout << "no\n";
        return;
    }
    if(n == 1) {
        cout << "yes\n";
        return;
    }
    for(int i = 1; i < pos.size(); i++) {
        if(pos[i] - pos[i - 1] <= 2) {
            cout << "yes\n";
            return;
        }
    }
    cout << "no\n";
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
