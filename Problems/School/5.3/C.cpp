#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    unordered_set<int> st;
    int n;
    cin >> n;
    bool ok = true;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if(st.count(x)) ok = false;
        st.insert(x);
    }
    cout << (ok ? "YES" : "NO") << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
