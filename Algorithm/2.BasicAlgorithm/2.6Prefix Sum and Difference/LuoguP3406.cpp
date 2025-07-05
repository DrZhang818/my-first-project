#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){ 
    int n, m;
    cin >> n >> m;
    vector<ll> a(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> a[i];
    }
    vector<ll> A(n), B(n), C(n);
    for(int i = 1; i <= n - 1; i++) {
        cin >> A[i] >> B[i] >> C[i];
    }
    vector<ll> D(n + 1);
    for(int i = 1; i <= m - 1; i++) {
        int l = a[i], r = a[i + 1];
        if(r < l) swap(l, r);
        D[l] += 1;
        D[r] -= 1;
    }
    ll ans = 0;
    for(int i = 1; i <= n - 1; i++) {
        D[i] += D[i - 1];
        if(A[i] * D[i] <= C[i] + B[i] * D[i]) {
            ans += A[i] * D[i];
        } else {
            ans += C[i] + B[i] * D[i];
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

