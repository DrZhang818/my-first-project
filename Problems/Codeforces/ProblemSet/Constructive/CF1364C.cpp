#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/1364/C
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    set<int> st;
    for(int i = 0; i <= n; i++) {
        st.insert(i);
    }
    for(int i = 1; i <= n; i++) {
        if(a[i] < a[i - 1] || a[i] > i) {
            cout << -1 << "\n";
            return;
        }
        st.erase(a[i]);
    }
    vector<int> ans(n + 1);
    for(int i = 1; i <= n; i++) {
        if(i != 1 && a[i] != a[i - 1]) {
            st.insert(a[i - 1]);
        }
        ans[i] = *st.begin();
        st.erase(*st.begin());
    }
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }
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
