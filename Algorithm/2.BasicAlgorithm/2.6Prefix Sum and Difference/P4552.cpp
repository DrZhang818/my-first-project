#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://www.luogu.com.cn/problem/P4552
void solve() { 
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> D(n + 1);    
    for(int i = 1; i <= n; i++) {
        D[i] = a[i] - a[i - 1];
    }    
    ll po = 0, ne = 0;
    for(int i = 2; i <= n; i++) {
        po += D[i] > 0 ? D[i] : 0;
        ne += D[i] < 0 ? -D[i] : 0;
    }
    cout << max(po, ne) << "\n";
    cout << abs(po - ne) + 1 << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
