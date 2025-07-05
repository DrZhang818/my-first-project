#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<long, long> PII;

struct infos{
    ll first;
    ll second;
};
void solve(){
    int n;
    cin >> n;
    vector<infos> info(n);
    for(int i = 0; i < n; i++){
        cin >> info[i].first >> info[i].second;
    }
    int cur = 0;
    ll ans = 0;
    bool ok = true;
    while(cur < n){
        ans++;
        if(ans < info[cur].first && (cur == 0 || info[cur - 1].second + 1 >= info[cur].first)){
            ans = info[cur].first;
        }
        else if(ans > info[cur].second || (cur == 0 || info[cur - 1].second + 1 < info[cur].first)){
            ok = false;
            cout << -1 << "\n";
            break;
        }
        cur++;
    }
    if(ok){
        cout << ans + 1 << "\n";
    }
}


int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    return 0;
}
