#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    multiset<int> st;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        st.insert(x);
    }    
    int m;
    cin >> m;
    for(int i = 0; i < m; i++) {
        int x;
        cin >> x;
        auto it = st.find(x);
        if(it == st.end()) {
            cout << "NO\n";
            return;
        }
        st.erase(it);
    }
    cout << "YES\n";
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
