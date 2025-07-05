#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int x;
    cin >> x;
    int y = x & (-x);
    for(int i = 0; i < 30; i++) {
        if((x >> i & 1) == 0) {
            y |= (1 << i);
            break;
        }
    }
    if(y >= x) {
        cout << "-1\n";
    } else {
        cout << y << "\n";
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
    
