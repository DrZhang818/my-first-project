#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    string s;
    cin >> s;
    int count = 0;
    int ans = 0;
    for(int i = 0; i < n;){
        if(s[i] == '0'){
            count++;
        }else{
            count = 0;
        }
        if(count >= m){
            count = 0;
            ans++;
            i += k;
        }else{
            i++;
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
