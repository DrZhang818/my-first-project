#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    ll x, k;
    cin >> x >> k;
    if(x > 1 && k > 1) {
        cout << "NO\n";
    } else if(x > 1 && k == 1) {
        for(int i = 2; i <= sqrt(x); i++) {
            if(x % i == 0) {
                cout << "NO\n";
                return;
            }
        }
        cout << "YES\n";
    } else if(x == 1 && k > 1) {
        while(k > 1) {
            x = x * 10 + x;
            k -= 1;
        }
        for(int i = 2; i <= sqrt(x); i++) {
            if(x % i == 0) {
                cout << "NO\n";
                return;
            }
        }
        cout << "YES\n";
    } else {
        cout << "NO\n";
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
    
