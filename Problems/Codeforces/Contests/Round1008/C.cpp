#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    vector<ll> b(2 * n + 1);
    for(int i = 1; i <= 2 * n; i++) {
        cin >> b[i];
    }
    sort(b.begin() + 1, b.end(), greater<ll>());
    vector<ll> a(2 * n + 2);
    int idx = 1;
    ll sum = 0;
    for(int i = 1; i <= 2 * n + 1; i += 2) {
        a[i] = b[idx++];
        sum += a[i];
    }
    for(int i = 2; i <= 2 * n - 1; i += 2) {
        a[i] = b[idx++];
        sum -= a[i];
    }
    a[2 * n] = sum;
    for(int i = 1; i <= 2 * n + 1; i++) {
        cout << a[i] << " \n"[i == 2 * n + 1];
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
    
