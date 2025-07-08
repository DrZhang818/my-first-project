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
    multiset<int> st;
    int ans = 1;
    st.insert(a[1]);
    for(int i = 2; i <= n; i++) {
        auto it = st.lower_bound(a[i]);
        if(it == st.begin()) {
            ans++;
            st.insert(a[i]);
        } else {
            it--;
            st.erase(it);
            st.insert(a[i]);
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
