#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    s = "#" + s;
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        if(s[i] == s[i - 1]) {
            ans += 1;
        }
    }
    ans = min((ll)n - 1, ans + 2 * k);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
