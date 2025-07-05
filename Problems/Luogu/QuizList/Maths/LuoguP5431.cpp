#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


int a[5000005], pre[5000005], inv[5000005]; 
int pow_mod(int a, int b, int MOD) {
    int res = 1;
    a %= MOD;
    while(b) {
        if(b & 1) res = (ll)res * a % MOD;
        a = (ll)a * a % MOD;
        b >>= 1;
    }
    return res;
}
void solve() { 
    int n, MOD, k;
    cin >> n >> MOD >> k;
    int tk = k;
    pre[0] = 1;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[i] = x;
        pre[i] = (ll)pre[i - 1] * x % MOD;
    }
    inv[n] = pow_mod(pre[n], MOD - 2, MOD);
    for(int i = n - 1; i >= 1; i--) {
        inv[i] = (ll)inv[i + 1] * a[i + 1] % MOD;
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        ans = (ans + (ll)pre[i - 1] * inv[i] % MOD * tk % MOD) % MOD;
        tk = (ll)tk * k % MOD;
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

