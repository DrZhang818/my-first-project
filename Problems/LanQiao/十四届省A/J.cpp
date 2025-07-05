#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    vector<int> a(n + 1);
    ll ans = 1;
    a[1] = 1;
    for(int i = 2; i <= n; i++) {
        if(a[i] == 0) {
            for(int j = i; j <= n; j += i) {
                a[j] ^= 1;
            }
            ans++;
        }
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
    
