#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


struct info{
    ll x;
    int flag;
};
void solve(){
    int n, k;
    cin >> n >> k;
    vector<ll> a(n), b(n);
    vector<info> infos(n * 2);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        infos[i].x = a[i];
        infos[i].flag = 0;
    }
    for(int i = 0; i < n; i++) {
        cin >> b[i];
        infos[n + i].x = b[i];
        infos[n + i].flag = 1;
    }   
    sort(infos.begin(), infos.end(), [](auto &a, auto &b){
        if(a.x != b.x) return a.x < b.x;
        return a.flag < b.flag;
    }); 
    
    ll ans = 0;
    int cur = 0, count = n;
    for(int i = 0; i < infos.size(); i++){
        if(infos[i].flag == 0){
            if(cur <= k){
                ans = max(ans, infos[i].x * count);
            }
            cur++;
        }
        else {
            if(cur <= k){
                ans = max(ans, infos[i].x * count);
            }
            int p = infos[i].x;
            while(infos[i].x == p){
                cur--;
                count--;
                i++;
            }
            i--;
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
