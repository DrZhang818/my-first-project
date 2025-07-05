#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    ll n;
    cin >> n;
    string s;
    cin >> s;
    ll c0 = 0, c1 = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '_') {
            c1++;
        } else {
            c0++;
        }
    }
    ll x, y;
    if(c0 % 2 == 0) {
        x = y = c0 / 2;
    } else {
        x = c0 / 2;
        y = x + 1;
    }
    cout << x * y * c1 << "\n";
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
    
