#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

const int MOD = 13331;
void solve(){   
    int n, m, LIM;
    cin >> n >> m >> LIM;
    vector<vector<ll>> C(1001, vector<ll>(1001));
    C[0][0] = 1;
    for(int i = 1; i <= 1000; i++){
        C[i][0] = C[i][i] = 1;
        for(int j = 1; j < i; j++){
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
        }
    }
    ll ans = 0;
    if()
    cout << ans << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    return 0;
}