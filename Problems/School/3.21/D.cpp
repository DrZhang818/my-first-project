#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    ll a, b;
    cin >> a >> b;
    ll g = __gcd(a, b);
    unordered_set<ll> st1;
    for(int i = 2; i <= sqrt(g); i++) {
        while(g % i == 0) {
            st1.insert(i);
            g /= i;
        }
    }
    if(g != 1) st1.insert(g);
    int ans = st1.size();
    cout << ans + 1 << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
