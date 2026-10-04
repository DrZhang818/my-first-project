#include <bits/stdc++.h>
using namespace std;
namespace scc {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/scc.hpp"
}
namespace bridge_articulation {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/bridge_articulation.hpp"
}
namespace dinic {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/dinic.hpp"
}
namespace hopcroft_karp {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/hopcroft_karp.hpp"
}
namespace hld {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/hld.hpp"
}
namespace dsu_on_tree {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/dsu_on_tree.hpp"
}
namespace centroid_decomposition {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/centroid_decomposition.hpp"
}
int main(){int n=200000;vector<vector<int>>g(n+1);
for(int u=2;u<=n;u++)g[u].push_back(u-1),g[u-1].push_back(u);
{vector<vector<int>>a(n+1);for(int u=1;u<n;u++)a[u].push_back(u+1);scc::SCC s(a);assert(s.count==n);}
{bridge_articulation::Lowlink s(n);for(int u=1;u<n;u++)s.addEdge(u,u+1);s.work();assert(s.bridge[1]&&s.cut[n/2]&&!s.cut[1]);}
{dinic::Dinic s(n);for(int u=0;u<n-1;u++)s.addEdge(u,u+1,1);assert(s.maxFlow(0,n-1)==1);}
{hopcroft_karp::HK s(n,n);for(int u=1;u<n;u++){s.addEdge(u,u+1);s.addEdge(u,u);s.left[u]=u+1;s.right[u+1]=u;}s.addEdge(n,n);assert(s.solve()==n);}
{hld::HLD s(n);for(int u=1;u<n;u++)s.addEdge(u,u+1);s.work();assert(s.lca(n,n/2)==n/2&&s.rootedSize(n,1)==1);}
{dsu_on_tree::DSUOnTree s(g);int cur=0;s.run([&](int,int d){cur+=d;},[&](int u){assert(cur==n-u+1);});assert(cur==0);}
{centroid_decomposition::Centroid s(g);int dep=0;for(int u=1;u<=n;u++)dep=max(dep,s.level[u]);assert(dep<=18);}
cout<<"PASS 200000-vertex chains\n";
}
