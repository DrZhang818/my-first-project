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
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> mn(n + 1), mx(n + 1);
    set<int> st;
    for(int i = 1; i <= n; i++) {
        st.insert(i);
    }
    for(int i = 1; i <= n; i++) {
        if(a[i] != a[i - 1]) {
            mn[i] = mx[i] = a[i];
            st.erase(a[i]);
        }
    }
    auto it = st.begin();
    for(int i = 1; i <= n; i++) {
        if(!mn[i]) {
            mn[i] = *it;
            it++;
        }
    }
    for(int i = 1; i <= n; i++) {
        if(!mx[i]) {
            it = st.lower_bound(mx[i - 1]);
            it--;
            mx[i] = *it;
            st.erase(it);
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << mn[i] << " \n"[i == n];
    }
    for(int i = 1; i <= n; i++) {
        cout << mx[i] << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
