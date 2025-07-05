#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 1; i <= n - 1; i++) {
        cin >> a[i];
    }
    ll ans = a[1] + a[n - 1];
    for(int i = 1; i < n - 1; i++) {
        ans += min(a[i], a[i + 1]);
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
    
