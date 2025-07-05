#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    int c0 = 0, c1 = 0, d0 = (n + 1) / 2, d1 = n / 2;
    for(int i = 0; i < n; i++) {
        if(i % 2 == 0) {
            c0 += s[i] == '1';
            d0 -= t[i] == '1';
        } else {
            c1 += s[i] == '1';
            d1 -= t[i] == '1';
        }
    }
    if(c0 <= d1 && c1 <= d0) {
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
    
