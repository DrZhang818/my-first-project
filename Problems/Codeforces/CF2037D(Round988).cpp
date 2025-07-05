#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
/*tar : find the minimum op to across all ostacle
        Greedy := select the maxVal op 
        
*/
void solve(){
    int n, m, L;
    cin >> n >> m >> L;
    std::vector<int> l(n), r(n);
    for(int i = 0; i < n; i++){
        cin >> l[i] >> r[i];
    }
    std::vector<int> x(m), v(m);
    for(int i = 0; i < m; i++){
        cin >> x[i] >> v[i];
    }
    priority_queue<int> pq;
    ll cur = 1;
    int ans = 0;
    for(int i = 0, j = 0; i < n; i++){
        while(j < m && x[j] < l[i]){
            pq.push(v[j]);
            j++;
        }
        while(cur < r[i] - l[i] + 2){
            if(pq.empty()){
                cout << -1 << endl;
                return;
            }
            cur += pq.top();
            pq.pop();
            ans++;
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}