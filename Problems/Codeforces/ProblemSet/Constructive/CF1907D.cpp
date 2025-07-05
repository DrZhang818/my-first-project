#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n;
    cin >> n;
    vector<PII> a(n + 1);
    int mx = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
        mx = a[i].second > mx ? a[i].second : mx;
    }
    auto check = [&](ll x) -> bool {
        ll lo = 0, hi = 0;
        for(int i = 1; i <= n; i++) {
            lo -= x;
            hi += x;
            if(a[i].first > hi || a[i].second < lo) {
                return false;
            }
            lo = max(lo, (ll)a[i].first);
            hi = min(hi, (ll)a[i].second);
        }
        return true;
    };
    int l = -1, r = mx + 1;
    while(l + 1 < r) {
        ll mid = l + (r - l) / 2;
        if(check(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << r << "\n";
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
    
    