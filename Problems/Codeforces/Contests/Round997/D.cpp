#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


struct info{
    int cnt;
    int pre;
    int suf;
};
void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<info> t(11);
    vector<int> prefix(n);
    vector<int> cnt(11);
    ll ans = 0;
    for(int i = 0; i < n; i++){
        t[a[i]].cnt++;
        t[a[i]].pre++;
        t[a[i]].suf++;
        cnt[a[i]]++;
        ans += cnt[a[i]];
        for(int j = 1; j < a[i]; j++){
            t[j].suf++;
            if(t[j].pre == t[j].suf){
                cnt[j]++;
                ans += cnt[j];
            }
        }
        for(int j = a[i] + 1; j <= 10; j++){
            t[j].pre++;
            if(t[j].pre == t[j].suf){
                cnt[j]++;
                ans += cnt[j];
            }
        }
        prefix[i] = cnt[a[i]];
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