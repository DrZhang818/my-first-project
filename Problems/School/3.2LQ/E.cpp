#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    ll n, a, b, c;
    cin >> n >> a >> b >> c;
    vector<ll> A(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> A[i];
        A[i] += A[i - 1];
    }
    const int N = log2(n);
    vector<vector<ll>> ST(n + 1, vector<ll>(N + 1));
    for(int i = 1; i <= n; i++) {
        ST[i][0] = A[i - 1] - a * c * i;
    }
    for(int s = 1; s <= N; s++) {
        for(int i = 1; i + (1 << s - 1) <= n; i++) {
            ST[i][s] = min(ST[i][s - 1], ST[i + (1 << s - 1)][s - 1]);
        }
    }
    vector<int> lg(n + 1);
    lg[1] = 0;
    for(int i = 2; i <= n; i++) {
        lg[i] = lg[i >> 1] + 1;
    }
    int ans = 0;
    for(int r = 1; r <= n; r++) {
        ll cur = A[r] - a * b * r;
        int l = 1, len = lg[r], tr = r;
        while(len >= 0) {
            if(cur > ST[l][len]) {
                tr = l + (1 << len) - 1;
                len--;
            } else {
                l = tr - (1 << len) + 1;
                len--;
            }
        }
        if(cur > A[l - 1] - a * c * l) {
            ans = max(ans, r - l + 1);
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
    
