#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/contest/2072/problem/D

void solve() { 
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int mx = -1000000000, l = -1, r = -1; 
    for(int i = 1; i <= n; i++) {
        int u = a[i], cur = 0;
        for(int j = i; j <= n; j++) { 
            int v = a[j];
            if(u > v) {
                cur += 1;
            } else if(u < v) {
                cur -= 1;
            } 
            if(cur >= mx) {
                l = i;
                r = j;
                mx = cur;
            }
        }
    }
    cout << l << " " << r << "\n";
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
    
