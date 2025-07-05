#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://www.luogu.com.cn/problem/P2568
/*
    数学
    题意: 
        给定正整数n, 求1 <= x,y <= n且gcd(x,y)为素数的数对(x,y)的个数
    关键思考:
        

*/  

void solve() { 
    int n;
    cin >> n;
    vector<int> primes;
    primes.reserve(n);
    vector<int> phi(n + 1);
    iota(phi.begin(), phi.end(), 0);    
    vector<bool> vis(n + 1, false);
    for(int i = 2; i <= n; i++) {
        if(!vis[i]) {
            phi[i] = i - 1;
            primes.push_back(i);
            for(int j = 2; j <= n / i; j++) {
                vis[i * j] = true;
                phi[i * j] *= 1.0 - 1.0 / i;
            }
        }
    }
    vector<ll> sum(n + 1, false);
    sum[1] = 1;
    for(int i = 2; i <= n; i++) {
        sum[i] = sum[i - 1] + (ll)phi[i] * 2;
    }
    ll ans = 0;
    for(int p : primes) {
        int up = n / p;
        ans += sum[up];
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
    
