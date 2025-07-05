#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;



void solve(){
    string s;
    cin >> s;
    int x;
    cin >> x;
    int n = s.size();
    vector<int> ans(n, 1);
    for(int i = 0; i < n; i++){
        if(s[i] == '0'){
            if(i + x < n) ans[i + x] = 0;
            if(i - x >= 0) ans[i - x] = 0;
        }
    }
    for(int i = 0; i < n; i++){
        if(s[i] == '1'){
            int cnt = 0;
            if(i + x >= n || ans[i + x] == 0) cnt++;;
            if(i - x < 0 || ans[i - x] == 0) cnt++;
            if(cnt == 2){
                cout << -1 << "\n";
                return;
            }
        }
    }
    for(int i = 0; i < n; i++){
        cout << ans[i];
    }
    cout << "\n";
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