#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n, x;
    cin >> n >> x;
    int i = 0, msk = 0;
    for(; i < n && (x & i) == i; i++) {
        if(i == n - 1 && (msk | i) != x) {
            cout << x << " ";
        } else {
            msk |= i;
            cout << i << " ";
        }
    }
    while(i < n) {
        i++;
        cout << x << " ";
    }
    cout << "\n";
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
    
