#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    set<int> st;

    for(int i = 1; i <= n; i++) {
        cin >> b[i];
        st.insert(b[i]);
    }

    int m;
    cin >> m;
    map<int,int> mp;
    vector<int> d(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> d[i];
        mp[d[i]]++;
    }

    if(!st.contains(d[m])) {
        cout << "NO\n";
        return;
    }

    for(int i = 1; i <= n; i++) {
        if(a[i] != b[i]) {
            int t = mp[b[i]]--;
            if(t == 0) {
                cout << "NO\n";
                return;
            }
        }
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
