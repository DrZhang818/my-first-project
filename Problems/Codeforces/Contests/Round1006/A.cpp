#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n, k, p;
    cin >> n >> k >> p;
    k = abs(k);
    if((k + p - 1) / p <= n) {
        cout << (k + p - 1) / p << "\n";
    } else {
        cout << "-1\n";
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
    
