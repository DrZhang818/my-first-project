#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    set<int> st;
    for(int i = 1; i <= n; i++) {
        if(i <= n - k || i >= k + 1) {
            if(b[i] == -1) {
                b[i] = a[i];
            }
            if(b[i] != a[i]) {
                cout << "NO\n";
                return;
            }
        } else {
            st.insert(a[i]);
        }
    }

    for(int i = n - k + 1; i <= k; i++) {
        if(b[i] == -1) {
            continue;
        } 
        if(!st.contains(b[i])) {
            cout << "NO\n";
            return;
        }
        st.erase(b[i]);
    }

    cout << "YES\n";
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
