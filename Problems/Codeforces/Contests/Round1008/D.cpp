#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    char op1, op2;
    int x, y;
    ll c1 = 1, c2 = 1;
    vector<ll> f1(n + 2, 1), f2(n + 2, 1), a1(n + 2), a2(n + 2);
    for(int i = 1; i <= n; i++) {
        cin >> op1 >> x >> op2 >> y;
        if(op1 == '+') a1[i] = x;
        else f1[i] = x;
        if(op2 == '+') a2[i] = y;
        else f2[i] = y;
    }
    vector<ll> sf1(n + 2, 0), sf2(n + 2, 0);
    for(int i = n; i >= 1; i--) {
        sf1[i] = sf1[i + 1] + f1[i] - 1;
        sf2[i] = sf2[i + 1] + f2[i] - 1;
    }
    for(int i = 1; i <= n; i++) {
        ll add = 0;
        if(a1[i]) {
            add += a1[i];
        } else {
            add += f1[i] * c1 - c1;
        }
        if(a2[i]) {
            add += a2[i];
        } else {
            add += f2[i] * c2 - c2;
        }

        if(!a1[i + 1] && !a2[i + 1]) {
            if(f1[i + 1] == f2[i + 1]) {
                if(sf1[i + 1] >= sf2[i + 1]) {
                    c1 += add;
                } else {
                    c2 += add;
                }
            } else {
                if(f1[i + 1] >= f2[i + 1]) {
                    c1 += add;
                } else {
                    c2 += add;
                }
            }
        } else if(a1[i + 1] && !a2[i + 1]) {
            c2 += add;
        } else if(a2[i + 1] && !a1[i + 1]) {
            c1 += add;
        } else {
            if(sf1[i + 1] >= sf2[i + 1]) {
                c1 += add;
            } else {
                c2 += add;
            }
        }
    }
    ll ans = c1 + c2;
    cout << ans << "\n";
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
    
