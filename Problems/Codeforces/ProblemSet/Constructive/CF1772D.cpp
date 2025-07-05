#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/problemset/problem/1772/D
constexpr int inf = 1000000000;
void solve() { 
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int lo = -inf, hi = inf;
    for(int i = 1; i <= n - 1; i++) {
        if(a[i] > a[i + 1]) {
            lo = max(lo, (a[i] + a[i + 1] + 1) / 2);
        } else if(a[i] < a[i + 1]) {
            hi = min(hi, (a[i] + a[i + 1]) / 2);
        }
    }
    if(lo > hi) {
        cout << -1 << "\n";
    } else {
        cout << hi << "\n";
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
    
