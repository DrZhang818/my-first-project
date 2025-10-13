#include<bits/stdc++.h>
using namespace std;
using ll=long long ;
const int N=2e5+10;

int f[N];
inline int find(int x){return x==f[x]?x:f[x]=find(f[x]);}
struct edge
{
    int u,v;
    ll w;
    int id;
    const bool operator < (const edge &x)const {return w<x.w;}
}E[N*3];
struct mst
{
    int v;ll w;int id;
};
vector<mst> e[N];

int fa[N][22],oddmx[N][22],evenmx[N][22];
int dep[N],vis_edge[N*3];
inline void dfs(int x)
{
    for(auto [v,w,id]:e[x])
    {
        if(v==fa[x][0]||vis_edge[id]==0)continue;
        fa[v][0]=x;
        w%2==0 ? evenmx[v][0]=w : oddmx[v][0]= w;  
        dep[v]=dep[x]+1;
        dfs(v);
    }
}

class PathMax
{
public:
    PathMax(int n)
    {
        for(int i=1;i<=n;++i)
        {
            dep[i]=0;
            for(int j=0;j<=20;++j)
                fa[i][j]=oddmx[i][j]=evenmx[i][j]=0;
        }
         
        dep[1]=1,dfs(1);
        for(int j=1;j<=20;++j)
            for(int i=1;i<=n;++i)   
                fa[i][j]=fa[fa[i][j-1]][j-1],
                oddmx[i][j]=max(oddmx[fa[i][j-1]][j-1],oddmx[i][j-1]),
                evenmx[i][j]=max(evenmx[fa[i][j-1]][j-1],evenmx[i][j-1]);
    }
    inline int oddquery(int x,int y)
    {
        int ans=0;
        if(dep[x]<dep[y])swap(x,y);
        for(int i=20;i>=0;--i)
            if(dep[fa[x][i]]>=dep[y])ans=max(ans,oddmx[x][i]),x=fa[x][i];
        if(x==y)return ans;

        for(int i=20;i>=0;--i)
            if(fa[x][i]!=fa[y][i])ans=max(ans,max(oddmx[x][i],oddmx[y][i])),x=fa[x][i],y=fa[y][i];

        return max(ans,max(oddmx[x][0],oddmx[y][0]));
    }
    inline int evenquery(int x,int y)
    {
        int ans=0;
        if(dep[x]<dep[y])swap(x,y);
        for(int i=20;i>=0;--i)
            if(dep[fa[x][i]]>=dep[y])ans=max(ans,evenmx[x][i]),x=fa[x][i];
        if(x==y)return ans;

        for(int i=20;i>=0;--i)
            if(fa[x][i]!=fa[y][i])ans=max(ans,max(evenmx[x][i],evenmx[y][i])),x=fa[x][i],y=fa[y][i];

        return max(ans,max(evenmx[x][0],evenmx[y][0]));
    }
};

int n,m;
inline void reset()
{
    for(int i=1;i<=n;++i)f[i]=i,e[i].clear();
    for(int i=1;i<=m;++i)vis_edge[i]=0;
}

inline void solve()
{
    cin>>n>>m;
    reset();

    int u,v;ll w;
    for(int i=1;i<=m;++i)
    {
        cin>>u>>v>>w;
        e[u].push_back({v,w,i});
        e[v].push_back({u,w,i});
        E[i]={u,v,w,i};
    }

    //MST
    sort(E+1,E+m+1);
    ll tmpans=0;int cnt=0;
    for(int i=1;i<=m;++i)
    {
        int fx=find(E[i].u),fy=find(E[i].v);
        if(fx==fy)continue;
        tmpans+=E[i].w;
        f[fx]=fy;
        vis_edge[E[i].id]=1;
        cnt++;
    }
    if(cnt!=n-1)return cout<<-1<<' '<<-1<<'\n',void();
    //calculate_ans
    vector<ll> ans(2);
    int p=(tmpans&1ll);
    ans[p]=tmpans,ans[p^1]=1e18;

    PathMax tr(n);
    //traverse all edges
    for(int i=1;i<=m;++i)
    {
        u=E[i].u,v=E[i].v,w=E[i].w;
        int id=E[i].id;
        if(vis_edge[id])continue;
        if(w%2==0)ans[p^1]=min(ans[p^1],ans[p]+w-tr.oddquery(u,v));
        else ans[p^1]=min(ans[p^1],ans[p]+w-tr.evenquery(u,v));
    }
    if(ans[p^1]==(ll)1e18)ans[p^1]=-1;
    cout<<ans[0]<<' '<<ans[1]<<'\n';
}
/*
1
2 1
1 2 5

1
3 1
1 3 1

1
4 4
1 2 1
1 3 1
1 4 1
2 4 2
*/
signed main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int T=1;
    cin>>T;
    while(T--)solve();
    return 0;
}