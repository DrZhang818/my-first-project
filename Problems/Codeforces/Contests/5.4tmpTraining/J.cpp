#include<bits/stdc++.h>
//#define int long long
#define ll long long
using namespace std;
const int INF = 2e9;
const int M = 1e6+5e5+5;
const int N = 5e5+5;
int n,t,m,k;
vector<pair<int,int>> graph[M];
map<int,int> hv[N];
bool vis[M];
pair<int,int> dis[M];
int idx;
vector<int> loc[N];
pair<int,int> tic[N];
void dij(){
    for(int i=1;i<=idx;i++){
        vis[i] = false;
        dis[i] = make_pair(INF,INF);
    }
    dis[1] = make_pair(1,0);
    priority_queue<pair<pair<int,int>,int>,vector<pair<pair<int,int>,int>>,greater<>> q;
    q.push(make_pair(make_pair(1,0),1));
    while(!q.empty()){
        auto p = q.top();
        q.pop();
        int x = p.second;
        if(vis[x]) continue;
        vis[x] = true;
        for(auto it:graph[x]){
            int ve = it.first;
            int w = it.second;
            if(x>n){
                if(ve>n){
                    if(tic[dis[x].first].second-dis[x].second>=w){
                        pair<int,int> pp = make_pair(dis[x].first,w+dis[x].second);
                        if(pp<dis[ve]){
                            dis[ve] = pp;
                            if(!vis[ve]){
                                q.push(make_pair(dis[ve],ve));
                            }
                        }
                    }
                }else{
                    pair<int,int> pp = make_pair(dis[x].first+1,0);
                    if(pp<dis[ve]){
                        dis[ve] = pp;
                        if(!vis[ve]){
                            q.push(make_pair(dis[ve],ve));
                        }
                    }
                }
            }else{
                auto it2 = lower_bound(loc[w].begin(),loc[w].end(),dis[x].first);
                if(it2!=loc[w].end()){
                    pair<int,int> pp = make_pair(*it2,0);
                    if(pp<dis[ve]){
                        dis[ve] = pp;
                        if(!vis[ve]){
                            q.push(make_pair(dis[ve],ve));
                        }
                    }
                }
            }
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>t;
    while(t--){
        cin>>n>>m>>k;
        //clear
        int u,v,c,l;
        idx = n;
        for(int i=1;i<=m;i++){
            cin>>u>>v>>c>>l;
            if(!hv[u].contains(c)){
                hv[u][c] = ++idx;
                graph[u].emplace_back(hv[u][c],c);
                graph[hv[u][c]].emplace_back(u,0);
            }   
            if(!hv[v].contains(c)){
                hv[v][c] = ++idx;
                graph[v].emplace_back(hv[v][c],c);
                graph[hv[v][c]].emplace_back(v,0);
            }
            graph[hv[u][c]].emplace_back(hv[v][c],l);
            graph[hv[v][c]].emplace_back(hv[u][c],l);
        }
        for(int i=1;i<=k;i++){
            cin>>tic[i].first>>tic[i].second;
            loc[tic[i].first].push_back(i);
        }
        dij();
        for(int i=1;i<=n;i++){
            if(dis[i].first!=INF){
                cout<<1;
            }else{
                cout<<0;
            }
        }
        cout<<"\n";
        for(int i=1;i<=n;i++){
            hv[i].clear();
        }
        for(int i=1;i<=m;i++){
            loc[i].clear();
        }
        for(int i=1;i<=idx;i++){
            graph[i].clear();
        }
    }
    return 0;
}