#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

struct info{
    ll time;
    int flag;    
};
void solve(){
    ll n, m, k;
    cin >> n >> m >> k;
    vector<vector<info>> infos(n + 1, vector<info>());
    int curAC = 0;
    for(int i = 0; i < k; i++){
        int a, b;
        cin >> a >> b;
        string s;
        cin >> s;
        int flag = -1;
        if(s == "Accepted"){
            flag = 1;
        }
        else if(s == "Rejected"){
            flag = 0;
        }else{
            flag = 2;
        }
        infos[b].push_back({a, flag});
    }
    ll curTime = 0;
    vector<ll> pre;
    for(auto &ifo : infos){
        sort(ifo.begin(), ifo.end(), [](const info& a, const info& b) -> bool{
            return a.time < b.time;
        });
        ll temp = 0;
        ll temp1 = 0;
        ll temp2 = 0;
        bool have1 = false;
        bool have2 = false;
        for(auto &p : ifo){
            if(p.flag == 0){
                temp += 1;
            }
            if(p.flag == 2 && !have2){
                temp2 = temp * 20 + p.time;
                have2 = true;
            }
            if(p.flag == 1){
                curAC++;
                have1 = true;
                temp1 = temp * 20 + p.time;
                break;
            }
        }
        if(have1 && have2){
            curTime += temp2;
        }
        else if(have1 && (!have2)){
            curTime += temp1;
        }else if(have2 && (!have1)){
            pre.push_back(temp2);
        }
    }
    sort(pre.begin(), pre.end());
    pre.insert(pre.begin(), 0);
    
    for(int x = 1; x <= n; x++){
        if(x < curAC){
            cout << "-1" << " ";
            continue;
        }
        int need = x - curAC;
        if(pre.size() - 1 < need){
            cout << "-1" << " ";
            continue;
        }
        curTime += pre[need];
        cout << curTime << " ";
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