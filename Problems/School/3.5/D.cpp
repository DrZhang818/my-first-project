#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    ll mx = 0, flag = 0;
    int idx = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(abs(a[i]) > mx) {
            flag = a[i] < 0 ? 1 : 0;
            mx = abs(a[i]);
            idx = i;
        }   
    }
    if(flag) {
        for(int i = 1; i <= n; i++) {
            a[i] = -a[i];
        }
    }
    vector<PII> ans;
    if(!flag) {
        for(int i = 2; i <= n; i++) {
            while(a[i] < a[i - 1]) {
                a[i] += mx;
                ans.push_back({idx, i});
                if(a[i] > mx) {
                    mx = a[i];
                    idx = i;
                }
            } 
        }
    } 
    else {
        for(int i = n - 1; i >= 1; i--) {
            while(a[i] < a[i + 1]) {
                a[i] += mx;
                ans.push_back({idx, i});
                if(a[i] > mx) {
                    mx = a[i];
                    idx = i;
                }
            } 
        }
    }
    cout << (int)ans.size() << "\n";
    for(int i = 0; i < (int)ans.size(); i++) {
        cout << ans[i].first << " " << ans[i].second << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
