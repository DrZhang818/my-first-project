#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[100001],n,t;
bool f;
vector<pair<int,int>>p[60];
queue<pair<int,int>>q;
signed main(){
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    for(cin>>t;t;t--){
        cin>>n;
        f=1;
        for(int j=59;j>=0;j--){
            p[j].clear();
        }
        while(!q.empty()){
            q.pop();
        }
        for(int i=1;i<=n;i++){
            cin>>a[i];
            for(int j=59;j>=0;j--){
                if(a[i]&1LL<<j){
                    p[j].push_back(make_pair(i,a[i]));
                    break;
                }
            }
        }
        for(int j=59;f&&j>=0;j--){
            if(p[j].size()==0){
                continue;
            }else if(p[j].size()==2){
                p[j][0].second^=p[j][1].second;
                for(int k=59;k>=0;k--){
                    if(p[j][0].second&1LL<<k){
                        p[k].push_back(p[j][0]);
                        break;
                    }
                }
                q.push(p[j][1]);
            }else{
                f=0;
            }
        }
        if(f){
            cout<<q.size()<<'\n';
            while(!q.empty()){
                cout<<q.front().first<<' '<<q.front().second<<'\n';
                q.pop();
            }
        }else{
            cout<<-1<<'\n';
        }
    }
    return 0;
}