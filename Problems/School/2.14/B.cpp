#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve() { 
    int n;
    cin >> n;
    vector<int> a(n + 1);
    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    ll curs = 0;
    ll ans = 100000000;
    for(int i = 1; i <= n; i++) {
        curs += a[i];
        ans = min(ans, abs(sum - curs - curs));
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

