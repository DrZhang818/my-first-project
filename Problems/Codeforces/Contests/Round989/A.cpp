#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

void solve(){
    int n, m;
    cin >> n >> m;
    int l = max(n, m);
    int ans = 0;
    for(int i = l;; i++){
        if(i % n == i % m){
            ans = i;
            break;
        }
    }
    cout << ans << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
