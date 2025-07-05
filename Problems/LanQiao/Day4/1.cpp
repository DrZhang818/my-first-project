#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> pre(n), suf(n);
    int cur = 0;
    for(int i = 0; i < n; i++){
        if(s[i] == '1'){
            cur++;
        }
        else{
            cur = 0;
        }
        pre[i] = cur;
    }
    cur = 0;
    for(int i = n - 1; i >= 0; i--){
        if(s[i] == '1'){
            cur++;
        }
        else{
            cur = 0;
        }
        suf[i] = cur;
    }
    int ans = 0;
    for(int i = 0; i < n - k; i++){
        if(i == 0){
            ans = k + suf[i + k];
            continue;
        }
        ans = max(ans, k + pre[i - 1] + suf[i + k]);
    }
    cout << ans << "\n";
}
    
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}