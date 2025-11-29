#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    set<int> st;
    for(int i = 0; i <= n; i++) {
        st.insert(i);
    }
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        st.erase(x);
    }
    cout << *st.begin() << "\n";
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
