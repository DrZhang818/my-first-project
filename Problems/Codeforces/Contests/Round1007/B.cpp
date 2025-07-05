#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    ll n;
    cin >> n;
    ll tot = n * (n + 1) / 2;
    if(abs(sqrt(tot) - (ll)sqrt(tot)) < 1e-7) {
        cout << -1 << "\n";
        return;
    }
    vector<ll> a(n + 1);
    iota(a.begin(), a.end(), 0LL);
    ll cur = 0;
    for(int i = 1; i <= n - 1; i++) {
        cur += a[i];
        if(abs(sqrt(cur) - (ll)sqrt(cur)) < 1e-7) {
            cur = cur - a[i] + a[i + 1];
            swap(a[i + 1], a[i]);
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << a[i] << " \n"[i == n];
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
    
