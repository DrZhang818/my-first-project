#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;


void solve(){
    int n;
    cin >> n;
    priority_queue<int> pos0;
    priority_queue<int, vector<int>, greater<int>> pos2;
    set<int> pos1;
    for(int i = 1; i <= n; i++){
        int x;
        cin >> x;
        if(x == 0){
            pos0.push(i);
        }else if(x == 1){
            pos1.insert(i);
        }else{
            pos2.push(i);
        }
    }
    int ans = 0;
    vector<PII> q;
    while((!pos1.empty() && !pos2.empty() && *pos1.rbegin() > pos2.top()) || 
            (!pos1.empty() && !pos0.empty() && *pos1.begin() < pos0.top())){
        if(!pos1.empty() && !pos2.empty() && *pos1.rbegin() > pos2.top()){
            q.push_back({*pos1.rbegin(), pos2.top()});
            int t1 = *pos1.rbegin(), t2 = pos2.top();
            pos1.erase(prev(pos1.end()));
            pos2.pop();
            pos1.insert(t2);
            pos2.push(t1);
            ans++;
        }
        if(!pos1.empty() && !pos0.empty() && *pos1.begin() < pos0.top()){
            q.push_back({pos0.top(), *pos1.begin()});
            int t1 = *pos1.begin(), t0 = pos0.top();
            pos1.erase(pos1.begin());
            pos0.pop();
            pos1.insert(t0);
            pos0.push(t1);
            ans++;
        }
    }
    cout << ans << "\n";
    for(auto &[x, y] : q){
        cout << x << " " << y << "\n";
    }
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
