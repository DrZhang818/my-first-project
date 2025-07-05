#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    int n;
    cin >> n; 
    string s;
    cin >> s;
    int ans = 0;
    bool ok = true;
    for(int i = 0; i < n; i++) {
        if(ok && s[i] == '1') {
            ans += 1;
            ok = false;
        }
        if(!ok && s[i] == '0') {
            ans += 1;
            ok = true;
        }
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

