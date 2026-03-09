#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;

    int st = 0;
    vector<int> nxt(n + 1);

    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if(x == -1) {
            st = i;
        } else {
            nxt[x] = i;
        }
    }

    for(int i = 1; i <= n; i++) {
        cout << st << " \n"[i == n];
        st = nxt[st];
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
