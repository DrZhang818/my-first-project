#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n;
    cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    if(n == 1 || n == 2){
        cout << (n == 1 ? 0 : max(a[0], a[1])) << "\n";
        return ;
    }
    ll ans = 0;
    for(int i = 0; i < n; i += 2){
        ans += a[i];
    }
    vector<ll> odd(n + 1, 0), even(n + 1, 0);
    for(int i = 1; i <= n; i++){
        odd[i] = odd[i - 1];
        even[i] = even[i - 1];  
        if(i & 1){
            even[i] += a[i - 1];
        }else{
            odd[i] += a[i - 1];
        }
    }
    ll mx = LLONG_MIN / 2, mn = LLONG_MAX / 2;
    ll del = 0;
     // for(int i = 0; i <= n; i++){
     //    cout << odd[i] - even[i] << " ";
     // }
     // cout << "\n";
    for(int i = 0; i <= n; i += 2){
        del = max(del, odd[i] - even[i] - mn);
        mn = min(mn, odd[i] - even[i]);
    }
    // cout << del << "\n";
    
    mx = LLONG_MIN / 2, mn = LLONG_MAX / 2;
    for(int i = 1; i <= n; i += 2){
        del = max(del, odd[i] - even[i] - mn);
        mn = min(mn, odd[i] - even[i]);
    }
    del = max(del, mx - mn);
    // cout << del << "\n";
    cout << ans + del << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}