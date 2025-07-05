#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;



void solve(){
    int l, r;
    cin >> l >> r;
    int ans = r - l;
    if(l == 1 && r == 1){
        cout << 1 << "\n";
        return;
    }else{
        cout << ans << "\n";
    }
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