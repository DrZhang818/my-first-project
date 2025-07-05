#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    multiset<ll> st;
    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j++) {
            st.insert(a[j] - a[i - 1]);
        }
    }
    ll ans = LLONG_MAX;
    for(int i = 1; i < n; i++) {
        for(int j = i; j <= n; j++) {
            auto pos = st.find(a[j] - a[i - 1]);
            st.erase(pos);
        }
        for(int j = 1; j <= i; j++) {
            ll cur = a[i] - a[j - 1];
            auto pos = st.lower_bound(cur);
            if(pos != st.end()) ans = min(ans, abs(*pos - cur));
            if(pos != st.begin()) pos--, ans = min(ans, abs(*pos - cur));
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
