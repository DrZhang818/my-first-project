#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

const ll MOD = 1e9 + 7;

ll power_pow(ll a, ll b){
    ll res = 1;
    a %= MOD;
    while(b > 0){
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void solve(){
    int n, m;
    cin >> n >> m;
    vector<PII> info(m);
    for(int i = 0; i < m; i++){
        cin >> info[i].first >> info[i].second;
    }
    sort(info.begin(), info.end(), [](PII a, PII b) -> bool{
        return a.second < b.second;
    });
    
    vector<int> ans(n, 0);
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < m; j++){
            if(info[j].second > i) break;

            if(info[j].first == 1){
                ans[i - 1] = (ans[i - 1] + i - info[j].second + 1) % MOD;
            }else{
                ans[i - 1] = (ans[i - 1] + power_pow(i - info[j].second + 1, 2)) % MOD;
            }
        }
    }
    for(int i = 0; i < n; i++){
        cout << ans[i] << " ";
    }
    cout << "\n";
}


int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}