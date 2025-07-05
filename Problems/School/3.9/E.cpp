#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }    
    ll sum = accumulate(a.begin() + 1, a.end(), 0);
    vector<ll> fac;
    for(ll i = 1; i <= sqrt(sum); i++) {
        if(sum % i == 0) {
            fac.push_back(i);
            if(i * i != sum) {
                fac.push_back(sum / i);
            }
        }
    }
    sort(fac.begin(), fac.end());
    vector<int> pre(n + 2), suf(n + 2);
    vector<int> rem(n + 1);
    auto check = [&](ll x) -> bool {
        for(int i = 1; i <= n; i++) rem[i] = a[i] % x;
        sort(rem.begin() + 1, rem.end());
        for(int i = 1; i <= n; i++) {
            pre[i] = pre[i - 1] + rem[i];
        }
        for(int i = n; i >= 1; i--) {
            suf[i] = suf[i + 1] + x - rem[i];
        }
        int cnt = 0;
        for(int i = 1; i <= n; i++) {
            if(pre[i] == suf[i + 1]) {
                cnt = pre[i];
                break;
            }
        }
        return cnt <= k;
    };
    int p = fac.size();
    for(int i = p - 1; i >= 0; i--) {
        if(check(fac[i])) {
            cout << fac[i] << "\n";
            return;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
