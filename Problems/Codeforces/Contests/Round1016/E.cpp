#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, k;
    cin >> n >> k;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int l = 0, r = n + 1;
    auto check = [&](int mid) -> bool {
        int cnt = 0;
        set<int> st;
        for(int i = 1; i <= n; i++) {
            if(a[i] < mid) st.insert(a[i]);
            if(st.size() == mid) {
                cnt++;
                st.clear();
            }
        }
        return cnt >= k;
    };
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << l << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
