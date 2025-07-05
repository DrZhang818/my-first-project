#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, k, q;
    cin >> n >> k >> q;
    ll sum = 0;
    vector<int> a(n + 1, k - q);
    for(int i = 1; i <= q; i++) {
        int x;
        cin >> x;
        a[x]++;
    }
    for(int i = 1; i <= n; i++) {
        if(a[i] > 0) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
