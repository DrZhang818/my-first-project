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
    int ans = 0;
    set<int> st;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(a[i]) {
            ans++;
        }
        st.insert(i);
    }
    if(a[1] == 0) {
        cout << ans + 1 << "\n";
        return;
    }
    vector<int> mex(n + 2);
    for(int i = n; i >= 1; i--) {
        st.erase(a[i]);
        mex[i] = *st.begin();
    }
    vector<int> mn(n + 1, inf);
    for(int i = 1; i <= n; i++) {
        mn[i] = mn[i - 1];
        if(a[i]) {
            mn[i] = min(mn[i], a[i]);
        }
    }
    for(int i = 1; i <= n; i++) {
        if(mn[i] < mex[i + 1]) {
            break;
        }
        if(a[i] == 0) {
            ans++;
            break;
        }
    }
    cout << ans << "\n";
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
