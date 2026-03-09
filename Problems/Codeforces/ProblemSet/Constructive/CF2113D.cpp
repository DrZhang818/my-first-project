#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }    
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    vector<int> suf_mx(n + 2);
    for(int i = n; i >= 1; i--) {
        suf_mx[i] = max(suf_mx[i + 1], a[i]);
    }

    stack<int> stk;
    vector<int> nxt(n + 1, n + 1);
    for(int i = n; i >= 1; i--) {
        while(!stk.empty() && b[i] <= b[stk.top()]) {
            stk.pop();
        }
        if(!stk.empty()) {
            nxt[i] = stk.top();
        }
        stk.push(i);
    }

    auto ck = [&](int x) {
        int j = 1;
        int lim = n + 1 - x;
        bool swaped = false;    
        
        for(int i = 1; i <= x;) {
            if(a[i] > b[j]) {
                i++;
                continue;
            }
            if(nxt[j] <= lim) {
                j = nxt[j];
            } else {
                if(swaped || suf_mx[x + 1] < b[j]) {
                    return false;
                }
                swaped = true;
                i++;
            }
        }
        return true;
    };

    int l = -1, r = n + 1;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(ck(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << l << "\n";
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
