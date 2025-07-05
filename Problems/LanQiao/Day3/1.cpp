#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int x, y;
    cin >> x >> y;
    x -= y;
    if(x < 0 || x % 2 == 1) {
        cout << "No\n";
        return ;
    }
    unsigned int t = ((unsigned int)(~y) << 1);
    while(t > 0 && x > 0){
        if((t & 1) == 0 && (x & 1) == 1){
            cout << "No\n";
            return;
        }
        t >>= 1;
        x >>= 1;
    }
    cout << "Yes\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}