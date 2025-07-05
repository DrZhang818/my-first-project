#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;



void solve(){
    int n, l, r;
    cin >> n >> l >> r;
    l--;
    r--;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    priority_queue<int> pq;
    for(int i = l; i <= r; i++){
        pq.push(a[i]);
    }
    ll ans = LLONG_MAX;
    for(int i = 0; i < l; i++){
        if(a[i] < pq.top()){
            pq.pop();
            pq.push(a[i]);
        }
    }
    ll cur = 0;
    while(!pq.empty()){
        cur += pq.top();
        pq.pop();
    }
    ans = min(ans, cur);
    cur = 0;
    for(int i = l; i <= r; i++){
        pq.push(a[i]);
    }
    for(int i = r + 1; i < n; i++){
        if(a[i] < pq.top()){
            pq.pop();
            pq.push(a[i]);
        }
    }
    while(!pq.empty()){
        cur += pq.top();
        pq.pop();
    }
    ans = min(ans, cur);
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