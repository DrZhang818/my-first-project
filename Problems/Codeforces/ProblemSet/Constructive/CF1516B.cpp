#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://codeforces.com/problemset/problem/1516/B
void solve() { 
    int n;
    cin >> n;
    vector<int> a(n + 1);
    int res = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        res ^= a[i];
    }
    if(res == 0) {
        cout << "YES\n";
        return ;
    }
    int cur = 0, cnt = 0;
    for(int i = 1; i <= n; i++) {
        cur ^= a[i];
        if(cur == res) {
            cnt++;
            cur = 0;
        }
    }
    if(cnt >= 3) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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
    
