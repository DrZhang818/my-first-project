#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n;
    cin >> n;
    db ans = 0;
    for(int i = 0; i < n; i++) {
        db x;
        cin >> x;
        ans += ((db)1 / x);
    }
    ans = (db)1 / ans;
    cout << fixed << setprecision(7) << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
