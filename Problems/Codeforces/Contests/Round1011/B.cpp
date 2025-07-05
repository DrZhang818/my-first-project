#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    vector<int> a(n + 1);
    // bool ok = false;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        // if(a[i]) ok = true;
    }
    auto it = find(a.begin() + 1, a.end(), 0);
    if(it == a.end()) {
        cout << 1 << "\n";
        cout << 1 << " " << n << "\n";
        return;
    }
    vector<PII> ans;
    if(a[1] != 0 && a[n] != 0) {
        int l = 1, r = n;
        while(a[l] != 0) l++;
        while(a[r] != 0) r--;
        if(l != r) {
            ans.push_back({1, l});
            n -= l - 1;
            ans.push_back({2, n});
            ans.push_back({1, 2});
        } else {
            ans.push_back({1, l});
            n -= l - 1;
            ans.push_back({1, n});
        }
    } else {
        if(a[1] == 0 && a[n] != 0) {
            ans.push_back({1, n - 1});
            ans.push_back({1, 2});
        } else if(a[1] != 0 && a[n] == 0) {
            ans.push_back({2, n});
            ans.push_back({1, 2});
        } else {
            ans.push_back({1, n / 2});
            n -= n / 2 - 1;
            ans.push_back({2, n});
            ans.push_back({1, 2});
        }
    }
    cout << ans.size() << "\n";
    for(auto [l, r] : ans) {
        cout << l << " " << r << "\n";
    }
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
    
