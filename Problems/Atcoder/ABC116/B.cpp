#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int s;
    cin >> s;
    int c = 1;
    set<int> st;
    st.insert(s);
    while(1) {
        c++;
        int ns = s;
        if(s & 1) {
            ns = 3 * s + 1;
        } else {
            ns = s / 2;
        }
        if(st.contains(ns)) {
            cout << c << "\n";
            return;
        }
        st.insert(ns);
        s = ns;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
