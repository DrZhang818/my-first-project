#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

const int MOD = 1e9 + 7;
void solve(){
    int n, m;
    cin >> n >> m;
    ll asum = 0, bsum = 1;
    vector<ll> a(n), b(m);
    for(auto &num : a){
        cin >> num;
        asum = (asum + num) % MOD;
    }
    for(auto &num : b){
        cin >> num;
        bsum = bsum * num % MOD;
    }
    if(asum == bsum){
        cout << "YES\n";
    }else{
        cout << "NO\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}