#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){ 
    ll n, k, MOD, mn, mx;
    cin >> n >> k >> MOD >> mn >> mx;
    vector<ll> D(n + 2), A(n + 1), S(n + 1);
    bool ok = false;
    while(k--) {
        char c;
        cin >> c;
        if(c == 'A') {
            ok = false;
            ll l, r, x;
            cin >> l >> r >> x;
            D[l] += x;
            D[r + 1] -= x;
        } else {
            ll l, r;
            cin >> l >> r;
            if(ok) {
                cout << S[r] - S[l - 1] << "\n";
            } else {
                for(int i = 1; i <= n; i++) {
                    A[i] = D[i] + A[i - 1];
                    S[i] = S[i - 1] + (mn <= A[i] * i % MOD && A[i] * i % MOD <= mx);
                }
                cout << S[r] - S[l - 1] << "\n";
                ok = true;
            }
        }
    }
    cin >> k;
    if(!ok) {
        for(int i = 1; i <= n; i++) {
            A[i] = D[i] + A[i - 1];
            S[i] = S[i - 1] + (mn <= A[i] * i % MOD && A[i] * i % MOD <= mx);
        }
    }
    while(k--) {
        ll l, r;
        cin >> l >> r;
        cout << S[r] - S[l - 1] << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

