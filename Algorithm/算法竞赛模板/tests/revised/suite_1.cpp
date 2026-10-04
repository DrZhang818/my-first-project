#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using i64=long long;
mt19937 rng(712367);
int rnd(int l,int r){return uniform_int_distribution<int>(l,r)(rng);}
long long checks=0;
#define CHECK(x) do {++checks;if(!(x)){cerr<<"FAIL "<<__FILE__<<":"<<__LINE__<<" "<<#x<<"\n";abort();}} while(0)

namespace T18 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/topk.hpp"
void test(){
TopK<3>s;map<int,i64>a;for(int z=0;z<200;z++){int k=rnd(0,8),v=rnd(-50,50);if(!a.count(k))a[k]=v;else a[k]=max(a[k],i64(v));s.add(k,v);int b=rnd(-1,8),c=rnd(-1,8);i64 ans=-TopK<3>::INF;for(auto [k,v]:a)if(k!=b&&k!=c)ans=max(ans,v);CHECK(s.get(b,c)==ans);}
}
}

namespace T19 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/dijkstra.hpp"
void test(){
for(int z=0;z<100;z++){int n=8;Dijkstra s(n);vector<vector<i64>>d(n+1,vector<i64>(n+1,s.inf));for(int i=1;i<=n;i++)d[i][i]=0;for(int k=0;k<25;k++){int u=rnd(1,n),v=rnd(1,n),w=rnd(0,10);s.addEdge(u,v,w);d[u][v]=min(d[u][v],i64(w));}for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(d[i][k]!=s.inf&&d[k][j]!=s.inf)d[i][j]=min(d[i][j],d[i][k]+d[k][j]);for(int i=1;i<=n;i++){auto a=s.run(i);CHECK(a==d[i]);}}
}
}

namespace T20 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/zero_one_bfs.hpp"
void test(){
for(int z=0;z<100;z++){int n=8;BFS01 s(n);vector<vector<int>>d(n+1,vector<int>(n+1,s.inf));for(int i=1;i<=n;i++)d[i][i]=0;for(int k=0;k<25;k++){int u=rnd(1,n),v=rnd(1,n),w=rnd(0,1);s.addEdge(u,v,w);d[u][v]=min(d[u][v],w);}for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(d[i][k]!=s.inf&&d[k][j]!=s.inf)d[i][j]=min(d[i][j],d[i][k]+d[k][j]);for(int i=1;i<=n;i++)CHECK(s.run(i)==d[i]);}
}
}

namespace T21 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/floyd.hpp"
void test(){
i64 inf=1e15;vector<vector<i64>>d(4,vector<i64>(4,inf));for(int i=1;i<=3;i++)d[i][i]=0;d[1][2]=-3;d[2][3]=5;floyd(d,inf);CHECK(d[1][3]==2);CHECK(d[3][1]==inf);
}
}

namespace T22 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/topological_sort.hpp"
void test(){
vector<vector<int>>g(5);g[1]={2,3};g[2]={4};auto p=toposort(g);CHECK(p.size()==4);vector<int>pos(5);for(int i=0;i<4;i++)pos[p[i]]=i;for(int u=1;u<=4;u++)for(int v:g[u])CHECK(pos[u]<pos[v]);g[4]={1};CHECK(toposort(g).empty());
}
}

namespace T23 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/kruskal.hpp"
void test(){
vector<Kruskal::Edge>e={{1,2,4},{2,3,-1},{1,3,2},{3,3,-99}};auto a=Kruskal::run(4,e);CHECK(a.first==1);CHECK(a.second.size()==2);
}
}

namespace T24 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/bipartite_degree_sequence.hpp"
void test(){
for(int z=0;z<300;z++){int n=3,m=3;vector<int>a(n+1),b(m+1);for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){int x=rnd(0,1);a[i]+=x;b[j]+=x;}vector<vector<int>>c;CHECK(BiDegree::run(n,m,a,b,c));for(int i=1;i<=n;i++)CHECK(accumulate(c[i].begin(),c[i].end(),0)==a[i]);for(int j=1;j<=m;j++){int s=0;for(int i=1;i<=n;i++)s+=c[i][j];CHECK(s==b[j]);}}vector<vector<int>>c;CHECK(!BiDegree::run(2,2,{0,2,2},{0,1,1},c));
}
}

namespace T25 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/incremental_apsp.hpp"
void test(){
for(int z=0;z<30;z++){int n=6;APSP s(n);vector<vector<i64>>d(n+1,vector<i64>(n+1,s.INF));for(int i=1;i<=n;i++)d[i][i]=0;for(int k=0;k<30;k++){int u=rnd(1,n),v=rnd(1,n),w=rnd(0,10);s.addDirected(u,v,w);d[u][v]=min(d[u][v],i64(w));for(int t=1;t<=n;t++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(d[i][t]!=s.INF&&d[t][j]!=s.INF)d[i][j]=min(d[i][j],d[i][t]+d[t][j]);CHECK(s.dis==d);}}
}
}

namespace T26 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/scc.hpp"
void test(){
for(int z=0;z<100;z++){int n=8;vector<vector<int>>g(n+1),r(n+1,vector<int>(n+1));for(int i=1;i<=n;i++)r[i][i]=1;for(int k=0;k<20;k++){int u=rnd(1,n),v=rnd(1,n);g[u].push_back(v);r[u][v]=1;}for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)r[i][j]|=r[i][k]&r[k][j];SCC s(g);for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)CHECK((s.id[i]==s.id[j])==bool(r[i][j]&&r[j][i]));}
}
}

namespace T27 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/two_sat.hpp"
void test(){
for(int z=0;z<300;z++){int n=5;TwoSAT s(n);vector<array<int,4>>a;for(int k=0;k<10;k++){array<int,4>v={rnd(1,n),rnd(0,1),rnd(1,n),rnd(0,1)};a.push_back(v);s.addClause(v[0],v[1],v[2],v[3]);}bool ok=false;for(int mask=0;mask<(1<<n);mask++){bool good=true;for(auto v:a)good&=(((mask>>(v[0]-1)&1)==v[1])||((mask>>(v[2]-1)&1)==v[3]));ok|=good;}CHECK(s.solve()==ok);if(ok)for(auto v:a)CHECK(s.answer[v[0]]==v[1]||s.answer[v[2]]==v[3]);s.setValue(1,true);s.setValue(1,false);CHECK(!s.solve());}
}
}

namespace T28 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/bridge_articulation.hpp"
void test(){
for(int z=0;z<200;z++){int n=7;Lowlink s(n);vector<pair<int,int>>e;for(int k=0;k<12;k++){int u=rnd(1,n),v=rnd(1,n);e.push_back({u,v});s.addEdge(u,v);}auto count=[&](int ban,int ed){vector<int>vis(n+1);int c=0;function<void(int)>dfs=[&](int u){vis[u]=1;for(int k=0;k<int(e.size());k++)if(k!=ed){auto [a,b]=e[k];if(a==u&&b!=ban&&!vis[b])dfs(b);if(b==u&&a!=ban&&!vis[a])dfs(a);}};for(int u=1;u<=n;u++)if(u!=ban&&!vis[u])c++,dfs(u);return c;};s.work();int base=count(0,-1);for(int i=0;i<int(e.size());i++)CHECK(s.bridge[i+1]==(count(0,i)>base));for(int u=1;u<=n;u++)CHECK(s.cut[u]==(count(u,-1)>base));}
}
}

namespace T29 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/edge_bcc.hpp"
void test(){
EdgeBCC s(4);s.addEdge(1,2);s.addEdge(2,3);s.addEdge(3,1);s.addEdge(3,4);s.work();CHECK(s.id[1]==s.id[3]);CHECK(s.id[3]!=s.id[4]);
}
}

namespace T30 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/vertex_bcc.hpp"
void test(){
VertexBCC s(6);s.addEdge(1,2);s.addEdge(2,3);s.addEdge(3,1);s.addEdge(3,4);s.addEdge(4,5);s.addEdge(5,3);s.work();CHECK(s.comp.size()==4);CHECK(s.cut[3]);CHECK(!s.cut[1]);int e=0;for(auto v:s.tree)e+=v.size();CHECK(e/2==int(s.tree.size())-3);for(int z=0;z<200;z++){int n=7;VertexBCC s(n);vector<vector<int>>g(n+1);for(int k=0;k<12;k++){int u=rnd(1,n),v=rnd(1,n);s.addEdge(u,v);g[u].push_back(v);g[v].push_back(u);}s.work();auto reach=[&](int a,int b,int ban){vector<int>vis(n+1);queue<int>q;q.push(a);vis[a]=1;while(!q.empty()){int u=q.front();q.pop();for(int v:g[u])if(v!=ban&&!vis[v])vis[v]=1,q.push(v);}return vis[b]!=0;};for(int u=1;u<=n;u++)for(int v=u+1;v<=n;v++){bool same=false;for(auto b:s.comp)if(find(b.begin(),b.end(),u)!=b.end()&&find(b.begin(),b.end(),v)!=b.end())same=true;bool ref=reach(u,v,0);for(int w=1;w<=n;w++)if(w!=u&&w!=v)ref&=reach(u,v,w);CHECK(same==ref);}}
}
}

namespace T31 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/euler_trail.hpp"
void test(){
vector<int>a;CHECK(EulerTrail::solve(4,{{1,2},{2,3},{3,1}},true,a));CHECK(a.size()==4);CHECK(!EulerTrail::solve(4,{{1,2},{3,4}},false,a));CHECK(EulerTrail::solve(2,{{1,1},{1,2},{1,2}},false,a));CHECK(a.size()==4);CHECK(EulerTrail::solve(0,{},false,a));
}
}

namespace T32 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/hopcroft_karp.hpp"
void test(){
for(int z=0;z<500;z++){int n=rnd(0,6),m=rnd(0,6);HK s(n,m);vector<vector<int>>g(n+1);for(int u=1;u<=n;u++)for(int v=1;v<=m;v++)if(rnd(0,2)==0)s.addEdge(u,v),g[u].push_back(v);function<int(int,int)>dfs=[&](int u,int mask){if(u>n)return 0;int ans=dfs(u+1,mask);for(int v:g[u])if(!(mask>>(v-1)&1))ans=max(ans,1+dfs(u+1,mask|(1<<(v-1))));return ans;};int ans=s.solve();CHECK(ans==dfs(1,0));CHECK(s.solve()==ans);auto [a,b]=s.minVertexCover();CHECK(a.size()+b.size()==size_t(ans));for(int u=1;u<=n;u++)for(int v:g[u])CHECK(find(a.begin(),a.end(),u)!=a.end()||find(b.begin(),b.end(),v)!=b.end());}
}
}

namespace T33 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/hungarian.hpp"
void test(){
for(int z=0;z<200;z++){int n=rnd(1,4),m=rnd(n,5);vector<vector<i64>>w(n+1,vector<i64>(m+1));for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)w[i][j]=rnd(-10,10);function<i64(int,int)>dfs=[&](int u,int mask){if(u>n)return 0LL;i64 ans=-100000;for(int v=1;v<=m;v++)if(!(mask>>(v-1)&1))ans=max(ans,w[u][v]+dfs(u+1,mask|(1<<(v-1))));return ans;};auto a=Hungarian::maximum(w);CHECK(a.first==dfs(1,0));}
}
}

namespace T34 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/dinic.hpp"
void test(){
for(int z=0;z<300;z++){int n=6;Dinic s(n);vector<array<int,3>>e;for(int k=0;k<15;k++){int u=rnd(0,n-1),v=rnd(0,n-1),c=rnd(0,5);s.addEdge(u,v,c);e.push_back({u,v,c});}i64 best=LLONG_MAX;for(int mask=0;mask<(1<<n);mask++)if((mask&1)&&!(mask>>(n-1)&1)){i64 c=0;for(auto a:e)if((mask>>a[0]&1)&&!(mask>>a[1]&1))c+=a[2];best=min(best,c);}CHECK(s.maxFlow(0,n-1)==best);auto cut=s.minCut(0);i64 val=0;for(auto a:e)if(cut[a[0]]&&!cut[a[1]])val+=a[2];CHECK(val==best);CHECK(s.maxFlow(0,n-1)==0);}
}
}

namespace T35 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/min_cost_flow.hpp"
void test(){
for(int z=0;z<150;z++){int n=4;MCF s(n);vector<array<int,4>>e;for(int k=0;k<6;k++){int u=rnd(0,n-2),v=rnd(u+1,n-1),c=rnd(0,2),w=rnd(-4,5);s.addEdge(u,v,c,w);e.push_back({u,v,c,w});}int lim=rnd(1,5),bf=-1; i64 bc=0;vector<int>b(n);function<void(int,i64)>dfs=[&](int k,i64 cost){if(k==int(e.size())){for(int i=1;i<n-1;i++)if(b[i])return;int f=-b[0];if(f<0||f>lim||b[n-1]!=f)return;if(f>bf || (f==bf&&cost<bc))bf=f,bc=cost;return;}auto a=e[k];for(int f=0;f<=a[2];f++){b[a[0]]-=f;b[a[1]]+=f;dfs(k+1,cost+f*a[3]);b[a[0]]+=f;b[a[1]]-=f;}};dfs(0,0);auto a=s.flow(0,n-1,lim);CHECK(a.first==bf&&a.second==bc);}
}
}
int main(){
T18::test(); cout<<"PASS topk "<<checks<<"\n";
T19::test(); cout<<"PASS dijkstra "<<checks<<"\n";
T20::test(); cout<<"PASS zero_one_bfs "<<checks<<"\n";
T21::test(); cout<<"PASS floyd "<<checks<<"\n";
T22::test(); cout<<"PASS topological_sort "<<checks<<"\n";
T23::test(); cout<<"PASS kruskal "<<checks<<"\n";
T24::test(); cout<<"PASS bipartite_degree_sequence "<<checks<<"\n";
T25::test(); cout<<"PASS incremental_apsp "<<checks<<"\n";
T26::test(); cout<<"PASS scc "<<checks<<"\n";
T27::test(); cout<<"PASS two_sat "<<checks<<"\n";
T28::test(); cout<<"PASS bridge_articulation "<<checks<<"\n";
T29::test(); cout<<"PASS edge_bcc "<<checks<<"\n";
T30::test(); cout<<"PASS vertex_bcc "<<checks<<"\n";
T31::test(); cout<<"PASS euler_trail "<<checks<<"\n";
T32::test(); cout<<"PASS hopcroft_karp "<<checks<<"\n";
T33::test(); cout<<"PASS hungarian "<<checks<<"\n";
T34::test(); cout<<"PASS dinic "<<checks<<"\n";
T35::test(); cout<<"PASS min_cost_flow "<<checks<<"\n";
}
