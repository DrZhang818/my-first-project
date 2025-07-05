#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    ll mid = 4LL * n * (n + 1) / 2;
    ll lo = mid - n, hi = mid + n;
    for(ll i = lo; i <= mid; i++) {
        cout << i << "^2";
        if(i == mid) cout << " =\n";
        else cout << " + ";
    }
    for(ll i = mid + 1; i <= hi; i++) {
        cout << i << "^2";
        if(i == hi) cout << "\n";
        else cout << " + ";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
