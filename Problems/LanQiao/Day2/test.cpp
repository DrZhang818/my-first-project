#include<bits/stdc++.h>
using namespace std;
const int N=100010;
vector<int>v[N];
int dl[N],dr[N];//vector<int>dl(N),dr(N);
queue<int>q;
void bfs(int x,int d[]/*vector<int>&d*/){
    memset(d,-1,sizeof(d));//fill(d.begin(),d.end(),-1);
    q.push(x);
    d[x]=0;
    while(q.size()){
        auto t=q.front();
        q.pop();
        for(auto u:v[t]){
            if(d[u]>=0)continue;
            d[u]=d[t]+1;
            q.push(u);
        }
    }
}
int main(){
    int n,w;
    cin>>n>>w;
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    int l,r;
    cin>>l>>r;
    bfs(l,dl);
    bfs(r,dr);
    int ans=0;
    for(int i=1;i<=n;i++)
    ans+=min(dl[i],dr[i])*w;
    cout<<ans<<endl;
    return 0;
}