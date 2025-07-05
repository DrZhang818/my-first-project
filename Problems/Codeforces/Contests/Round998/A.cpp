#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;



void solve(){
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int ans = 0;
    for(int i = -200; i <= 200; i++){
        int cur = 0;
        if(a + b == i){
            cur++;
        }
        if(b + i == c){
            cur++;
        }
        if(i + c == d){
            cur++;
        }
        ans = max(ans, cur);
    }
    cout << ans << "\n";
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