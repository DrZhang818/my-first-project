#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    ll s1 = 0, s2 = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        s1 += a[i];
        s2 ^= a[i];
    }
    cout << 2 << "\n" << s2 << " " << (s1 + s2) << "\n";
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
    
