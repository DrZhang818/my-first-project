#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int k;
    cin >> k;
    k *= 2;
    if(k % 4 != 0) {
        cout << -1 << "\n";
        return;
    }
    int x = (k >> 2);
    int y = k - x;
    if((x & y) == x) {
        cout << x << " " << y << "\n";
    } else {
        cout << -1 << "\n";
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
    
