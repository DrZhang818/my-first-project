#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/problemset/problem/1396/A
void solve() { 
    int n;
    cin >> n;
    vector<ll> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = ((a[i] % n) + n) % n;
    }
    if(n == 1) {
        cout << 1 << " " << 1 << "\n";
        cout << -a[1] << "\n";
        cout << 1 << " " << 1 << "\n";
        cout << 0 << "\n";
        cout << 1 << " " << 1 << "\n";
        cout << 0 << "\n";
        return;
    }
    vector<ll> ans(n + 1);
    for(int i = 1; i <= n; i++) {
        ans[i] = b[i] * (n - 1);
        a[i] += ans[i];
    }
    cout << 1 << " " << n - 1 << "\n";
    for(int i = 1; i <= n - 1; i++) {
        cout << ans[i] << " \n"[i == n - 1];
    }
    cout << 2 << " " << n << "\n";
    for(int i = 2; i <= n; i++) {
        if(i < n) cout << 0 << " ";
        else cout << ans[i] << "\n";
    }
    cout << 1 << " " << n << "\n";
    for(int i = 1; i <= n; i++) {
        cout << -a[i] << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
