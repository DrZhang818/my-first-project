#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using i64=long long;
mt19937 rng(712367);
int rnd(int l,int r){return uniform_int_distribution<int>(l,r)(rng);}
long long checks=0;
#define CHECK(x) do {++checks;if(!(x)){cerr<<"FAIL "<<__FILE__<<":"<<__LINE__<<" "<<#x<<"\n";abort();}} while(0)

namespace T36 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/lower_bound_flow.hpp"
void test(){
for(int z=0;z<200;z++){int n=3;BoundFlow s(n);vector<array<int,4>>e;for(int k=0;k<5;k++){int u=rnd(0,n-1),v=rnd(0,n-1),l=rnd(0,1),r=rnd(l,2);s.addEdge(u,v,l,r);e.push_back({u,v,l,r});}bool circ=false;int best=-1,least=100000;vector<int>b(n);function<void(int)>dfs=[&](int k){if(k==int(e.size())){if(b[0]==0&&b[1]==0&&b[2]==0)circ=true;if(!b[1]&&b[2]==-b[0]&&b[2]>=0)best=max(best,b[2]),least=min(least,b[2]);return;}auto a=e[k];for(int f=a[2];f<=a[3];f++){b[a[0]]-=f;b[a[1]]+=f;dfs(k+1);b[a[0]]+=f;b[a[1]]-=f;}};dfs(0);vector<i64>a;CHECK(s.circulation(a)==circ);BoundFlow::Result r;CHECK(s.maxFlow(0,2,r)==(best>=0));if(best>=0)CHECK(r.value==best);CHECK(s.minFlow(0,2,r)==(best>=0));if(best>=0)CHECK(r.value==least);}
}
}

namespace T37 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/difference_constraints.hpp"
void test(){
for(int z=0;z<500;z++){Diff s(6);for(int k=0;k<16;k++)s.le(rnd(1,6),rnd(1,6),rnd(-3,5));vector<__int128>a,b;bool x=s.solve(a),y=s.solve(b,false);CHECK(x==y);if(x)for(auto e:s.edges)CHECK(a[e.v]-a[e.u]<=e.w);}
}
}

namespace T38 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/functional_graph.hpp"
void test(){
for(int z=0;z<200;z++){int n=12;vector<int>a(n+1);for(int i=1;i<=n;i++)a[i]=rnd(1,n);FuncGraph s(a);for(int u=1;u<=n;u++){int x=u;for(int k=0;k<100;k++){CHECK(s.jump(u,k)==x);x=a[x];}for(int v=1;v<=n;v++){int ans=-1,x=u;for(int k=0;k<=n;k++,x=a[x])if(x==v){ans=k;break;}CHECK(s.dis(u,v)==ans);}}}FuncGraph s({0,2,1});CHECK(s.jump(1,UINT64_MAX)==2);
}
}

namespace T39 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/range_graph.hpp"
void test(){
for(int z=0;z<100;z++){int n=7;RangeGraph s(n);vector<vector<i64>>d(n+1,vector<i64>(n+1,s.INF));for(int i=1;i<=n;i++)d[i][i]=0;for(int k=0;k<20;k++){int l=rnd(1,n),r=rnd(l,n),x=rnd(1,n),y=rnd(x,n),w=rnd(0,10);s.rangeRange(l,r,x,y,w);for(int i=l;i<=r;i++)for(int j=x;j<=y;j++)d[i][j]=min(d[i][j],i64(w));}for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(d[i][k]!=s.INF&&d[k][j]!=s.INF)d[i][j]=min(d[i][j],d[i][k]+d[k][j]);for(int i=1;i<=n;i++)CHECK(s.distances(i)==d[i]);}
}
}

namespace T41 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/second_mst.hpp"
void test(){
for(int z=0;z<200;z++){int n=4,m=7;vector<SecondMST::Edge>e;for(int k=0;k<m;k++)e.push_back({rnd(1,n),rnd(1,n),rnd(-5,5)});set<i64>vals;for(int mask=0;mask<(1<<m);mask++)if(__builtin_popcount(unsigned(mask))==n-1){vector<int>p(n+1);iota(p.begin(),p.end(),0);function<int(int)>f=[&](int x){return x==p[x]?x:p[x]=f(p[x]);};bool ok=true;i64 w=0;for(int k=0;k<m;k++)if(mask>>k&1){int u=f(e[k].u),v=f(e[k].v);if(u==v)ok=false;p[u]=v;w+=e[k].w;}if(ok)vals.insert(w);}i64 a,b;CHECK(SecondMST::solve(n,e,a,b)==!vals.empty());if(!vals.empty()){CHECK(a==*vals.begin());CHECK(b==(vals.size()>1?*next(vals.begin()):SecondMST::INF));}}
}
}

namespace T43 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/xor_mst.hpp"
void test(){
for(int z=0;z<200;z++){int n=rnd(0,30);vector<uint32_t>a(n);for(auto&x:a)x=rnd(0,511);if(n&&z%2==0)a[0]|=1u<<31;auto ans=XorMST::run(a);vector<uint64_t>d(n,UINT64_MAX);vector<bool>v(n);uint64_t sum=0;if(n)d[0]=0;for(int k=0;k<n;k++){int u=-1;for(int i=0;i<n;i++)if(!v[i]&&(u<0||d[i]<d[u]))u=i;v[u]=1;sum+=d[u];for(int i=0;i<n;i++)d[i]=min(d[i],uint64_t(a[i]^a[u]));}CHECK(ans.first==int64_t(sum));CHECK(ans.second.size()==size_t(max(0,n-1)));}
}
}

namespace T44 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/max_weight_closure.hpp"
void test(){
for(int z=0;z<100;z++){int n=7;vector<i64>w(n+1);vector<pair<int,int>>e;for(int i=1;i<=n;i++)w[i]=rnd(-10,10);for(int k=0;k<12;k++)e.push_back({rnd(1,n),rnd(1,n)});i64 best=0;for(int m=0;m<(1<<n);m++){bool ok=true;for(auto [u,v]:e)if((m>>(u-1)&1)&&!(m>>(v-1)&1))ok=false;i64 s=0;for(int i=1;i<=n;i++)if(m>>(i-1)&1)s+=w[i];if(ok)best=max(best,s);}auto a=maxClosure(w,e);CHECK(a.first==best);}
}
}

namespace T45 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/boruvka.hpp"
void test(){
for(int z=0;z<200;z++){int n=8;vector<Boruvka::Edge>e;for(int k=0;k<20;k++)e.push_back({rnd(1,n),rnd(1,n),rnd(-20,20)});auto a=Boruvka::run(n,e);sort(e.begin(),e.end(),[](auto x,auto y){return x.w<y.w;});vector<int>p(n+1);iota(p.begin(),p.end(),0);function<int(int)>f=[&](int x){return x==p[x]?x:p[x]=f(p[x]);};i64 w=0;int cnt=n;for(auto v:e){int x=f(v.u),y=f(v.v);if(x!=y)p[x]=y,w+=v.w,--cnt;}CHECK(a.weight==w&&a.comp==cnt);}
}
}

namespace T47 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/tree_diameter.hpp"
void test(){
for(int z=0;z<100;z++){int n=20;vector<vector<TreeDiameter::Edge>>g(n+1);for(int u=2;u<=n;u++){int p=rnd(1,u-1),w=rnd(0,10);g[u].push_back({p,w});g[p].push_back({u,w});}i64 best=0;for(int s=1;s<=n;s++){function<void(int,int,i64)>dfs=[&](int u,int p,i64 d){best=max(best,d);for(auto [v,w]:g[u])if(v!=p)dfs(v,u,d+w);};dfs(s,0,0);}CHECK(TreeDiameter::run(g).dis==best);}
}
}

namespace T48 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/tree_centroids.hpp"
void test(){
for(int z=0;z<100;z++){int n=20;vector<vector<int>>g(n+1);for(int u=2;u<=n;u++){int p=rnd(1,u-1);g[u].push_back(p);g[p].push_back(u);}set<int>b;for(int u=1;u<=n;u++){int best=0;vector<bool>vis(n+1);vis[u]=true;function<int(int)>dfs=[&](int x){vis[x]=true;int c=1;for(int v:g[x])if(!vis[v])c+=dfs(v);return c;};for(int v:g[u])if(!vis[v])best=max(best,dfs(v));if(best*2<=n)b.insert(u);}auto a=centroids(g);CHECK(set<int>(a.begin(),a.end())==b);}
}
}

namespace T49 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/kruskal_reconstruction_tree.hpp"
void test(){
for(int z=0;z<100;z++){int n=10;vector<KRT::Edge>e;vector<vector<i64>>d(n+1,vector<i64>(n+1,999));for(int i=1;i<=n;i++)d[i][i]=-999;for(int k=0;k<20;k++){int u=rnd(1,n),v=rnd(1,n),w=rnd(-10,10);e.push_back({u,v,w});d[u][v]=d[v][u]=min(d[u][v],i64(w));}for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)d[i][j]=min(d[i][j],max(d[i][k],d[k][j]));KRT s(n,e);for(int u=1;u<=n;u++)for(int v=1;v<=n;v++){i64 a;CHECK(s.bottle(u,v,a)==(d[u][v]!=999));if(d[u][v]!=999)CHECK(a==(u==v?0:d[u][v]));}}
}
}

namespace T50 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/lca.hpp"
void test(){
for(int z=0;z<100;z++){int n=50;vector<vector<int>>g(n+1);vector<int>p(n+1),dep(n+1);for(int u=2;u<=n;u++){p[u]=rnd(1,u-1);dep[u]=dep[p[u]]+1;g[u].push_back(p[u]);g[p[u]].push_back(u);}LCA s(g);for(int k=0;k<100;k++){int u=rnd(1,n),v=rnd(1,n),x=u,y=v;while(dep[x]>dep[y])x=p[x];while(dep[y]>dep[x])y=p[y];while(x!=y)x=p[x],y=p[y];CHECK(s.lca(u,v)==x);CHECK(s.dis(u,v)==dep[u]+dep[v]-2*dep[x]);}}int n=200000;vector<vector<int>>g(n+1);for(int u=2;u<=n;u++)g[u].push_back(u-1),g[u-1].push_back(u);LCA s(g);CHECK(s.lca(100000,n)==100000);CHECK(s.jump(n,n)==0);
}
}

namespace T51 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/hld.hpp"
void test(){
for(int z=0;z<100;z++){int n=30;HLD s(n);vector<vector<int>>g(n+1);for(int u=2;u<=n;u++){int p=rnd(1,u-1);s.addEdge(u,p);g[u].push_back(p);g[p].push_back(u);}s.work();for(int r=1;r<=n;r++){vector<int>p(n+1),sz(n+1,1),ord{r};for(int i=0;i<int(ord.size());i++)for(int v:g[ord[i]])if(v!=p[ord[i]])p[v]=ord[i],ord.push_back(v);for(int i=n-1;i>0;i--)sz[p[ord[i]]]+=sz[ord[i]];for(int u=1;u<=n;u++){CHECK(s.rootedSize(r,u)==sz[u]);CHECK(s.rootedParent(r,u)==(u==r?r:p[u]));}}}
}
}

namespace T52 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/tree_difference.hpp"
void test(){
vector<vector<int>>g(6);for(auto [u,v]:vector<pair<int,int>>{{1,2},{1,3},{2,4},{2,5}})g[u].push_back(v),g[v].push_back(u);TreeDiff s(g);vector<i64>a(6),b(6);s.addVertexPath(a,4,3,7LL);s.addEdgePath(b,5,3,2LL);s.accumulate(a,s.parent,s.order);s.accumulate(b,s.parent,s.order);CHECK(a==vector<i64>({0,7,7,7,7,0}));CHECK(b==vector<i64>({0,0,2,2,0,2}));
}
}

namespace T53 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/virtual_tree.hpp"
void test(){
for(int z=0;z<200;z++){int n=40;vector<vector<int>>g(n+1);for(int u=2;u<=n;u++){int p=rnd(1,u-1);g[u].push_back(p);g[p].push_back(u);}VirtualTree s(g);vector<int>k;for(int i=0;i<rnd(0,15);i++)k.push_back(rnd(1,n));auto [r,e]=s.build(k);if(k.empty()){CHECK(r==0&&e.empty());continue;}set<int>a(k.begin(),k.end());for(int u:k)for(int v:k)a.insert(s.lca(u,v));set<int>b{r};for(auto [u,v]:e){CHECK(s.isAnc(u,v));b.insert(u);b.insert(v);for(int w:a)CHECK(w==u||w==v||!s.isAnc(u,w)||!s.isAnc(w,v));}CHECK(a==b);CHECK(e.size()+1==a.size());}
}
}

namespace T54 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/doubling.hpp"
void test(){
vector<int>a={0,2,3,0};vector<string>w={"","a","b","c"};struct Op{string operator()(string a,string b)const{return a+b;}};Doubling<string,Op>s(a,w,100,"");for(int u=1;u<=3;u++)for(int k=0;k<=100;k++){int x=u;string v;for(int i=0;i<k;i++)v+=w[x],x=a[x];CHECK(s.jump(u,k)==make_pair(x,v));}
}
}

namespace T55 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/dsu_on_tree.hpp"
void test(){
for(int z=0;z<100;z++){int n=40;vector<vector<int>>g(n+1);vector<int>c(n+1),cnt(10),ans(n+1);for(int u=1;u<=n;u++){c[u]=rnd(0,9);if(u>1){int p=rnd(1,u-1);g[u].push_back(p);g[p].push_back(u);}}DSUOnTree s(g);int cur=0;s.run([&](int u,int d){if(cnt[c[u]])cur--;cnt[c[u]]+=d;CHECK(cnt[c[u]]>=0);if(cnt[c[u]])cur++;},[&](int u){ans[u]=cur;});CHECK(cur==0);for(int u=1;u<=n;u++){set<int>a;for(int i=s.tin[u];i<=s.tout[u];i++)a.insert(c[s.euler[i]]);CHECK(ans[u]==int(a.size()));}}
}
}

namespace T56 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/centroid_decomposition.hpp"
void test(){
for(int z=0;z<100;z++){int n=60;vector<vector<int>>g(n+1);for(int u=2;u<=n;u++){int p=rnd(1,u-1);g[u].push_back(p);g[p].push_back(u);}Centroid s(g);int root=0;for(int u=1;u<=n;u++){if(!s.parent[u])root=u;else CHECK(s.level[u]==s.level[s.parent[u]]+1);}CHECK(root);vector<int>vis(n+1);function<void(int)>go=[&](int c){vis[c]=1;for(int v:g[c])if(!vis[v]){vector<int>stk{v};set<int>a{v};for(int i=0;i<int(stk.size());i++)for(int x:g[stk[i]])if(!vis[x]&&!a.count(x))a.insert(x),stk.push_back(x);CHECK(int(a.size())*2<=[&](){int k=1;for(int u=1;u<=n;u++){int x=u;while(x&&x!=c)x=s.parent[x];k+=x==c&&u!=c;}return k;}());}for(int u=1;u<=n;u++)if(s.parent[u]==c)go(u);};go(root);CHECK(count(vis.begin()+1,vis.end(),1)==n);}
}
}
int main(){
T36::test(); cout<<"PASS lower_bound_flow "<<checks<<"\n";
T37::test(); cout<<"PASS difference_constraints "<<checks<<"\n";
T38::test(); cout<<"PASS functional_graph "<<checks<<"\n";
T39::test(); cout<<"PASS range_graph "<<checks<<"\n";
T41::test(); cout<<"PASS second_mst "<<checks<<"\n";
T43::test(); cout<<"PASS xor_mst "<<checks<<"\n";
T44::test(); cout<<"PASS max_weight_closure "<<checks<<"\n";
T45::test(); cout<<"PASS boruvka "<<checks<<"\n";
T47::test(); cout<<"PASS tree_diameter "<<checks<<"\n";
T48::test(); cout<<"PASS tree_centroids "<<checks<<"\n";
T49::test(); cout<<"PASS kruskal_reconstruction_tree "<<checks<<"\n";
T50::test(); cout<<"PASS lca "<<checks<<"\n";
T51::test(); cout<<"PASS hld "<<checks<<"\n";
T52::test(); cout<<"PASS tree_difference "<<checks<<"\n";
T53::test(); cout<<"PASS virtual_tree "<<checks<<"\n";
T54::test(); cout<<"PASS doubling "<<checks<<"\n";
T55::test(); cout<<"PASS dsu_on_tree "<<checks<<"\n";
T56::test(); cout<<"PASS centroid_decomposition "<<checks<<"\n";
}
