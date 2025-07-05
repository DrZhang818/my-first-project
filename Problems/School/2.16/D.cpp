#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){ 
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] *= 2;
    }
    ll p = 0, cur = 0;
    for(int i = 0; i < n; i++) {
        cur += a[i] * (i % 2 == 0 ? 1 : -1);
    }
    p = cur / 2;
    for(int i = 0; i < n; i++) {
        cout << p << " ";
        p = a[i] - p;
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

