#include<bits/stdc++.h>
using namespace std;
vector<int> e[200010];
vector<pair<int,int>> mod;
int vis[200010];
int fa[200010];
// inline void dfs(int x)
// {
//     for(int v:e[x])
//     {
//         if(v==fa[x])continue;
//         if(vis[v])
//         {
//             mod.push_back({v,x});
//             int pos=x;
//             while(pos!=v)
//             {
//                 mod.push_back({pos,fa[pos]});
//                 pos=fa[pos];
//             }
//             continue;
//         }
//         vis[x]=1;
//         fa[v]=x;
//         dfs(v);
//     }
// }
void dfs(int x, int f) {
    vis[x] = true;
    fa[x] = f;
    for(int v : e[x]) {
        if(v == f) {
            continue;
        }
        if(vis[v]) {
            mod.push_back({v, x});
            int cur = x;
            while(cur != v) {
                cerr << cur << " " << fa[cur] << " " << v << "\n";
                mod.push_back({cur, fa[cur]});
                cur = fa[cur];
            }
            continue;
        }
        dfs(v, x);
    }
}
inline void solve()
{
    int n;
    cin>>n;
    vector<int> x(n+1),y(n+1),d(n+1);
    int c4=0,c5=0;
    for(int i=1;i<=n;++i)
    {
        cin>>x[i]>>y[i];
        d[x[i]]++,d[y[i]]++;
        e[x[i]].push_back(y[i]);
        e[y[i]].push_back(x[i]);
    }
    for(int i=1;i<=n;++i)
    {
        if(d[i]==4)c4++;
        if(d[i]==5)c5++;
        if(d[i]>5)assert(0);
    }
    dfs(1, 0);
    long long ans=0;
    for(auto [X,Y]:mod)
    {
        if(d[X]==5)c5--;
        if(d[X]==4)c4--;
        d[x[X]]--;
        if(d[X]==4)c4++;

        if(d[Y]==5)c5--;
        if(d[Y]==4)c4--;
        d[Y]--;
        if(d[Y]==4)c4++;

        if(c5==0)
        {
            ans+=n-c4;
            cout<<X<<' '<<Y<<' '<<c4<<' '<<c5<<' '<<n-c4<<'\n';
        }

        if(d[X]==4)c4--;
        d[X]++;
        if(d[X]==4)c4++;
        if(d[X]==5)c5++;

        if(d[Y]==4)c4--;
        d[Y]++;
        if(d[Y]==4)c4++;
        if(d[Y]==5)c5++;
        
    }
    cout<<ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    return solve(),0;
}