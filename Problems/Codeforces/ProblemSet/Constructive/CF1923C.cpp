#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(a[i] == 1) a[i] = a[i - 1] - 1;
        else a[i] += a[i - 1] - 1;
    }
    while(q--) {
        int l, r;
        cin >> l >> r;
        if(a[r] - a[l - 1] >= 0 && r - l >= 1) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
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