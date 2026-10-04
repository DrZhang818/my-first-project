#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using i64=long long;
mt19937 rng(712367);
int rnd(int l,int r){return uniform_int_distribution<int>(l,r)(rng);}
long long checks=0;
#define CHECK(x) do {++checks;if(!(x)){cerr<<"FAIL "<<__FILE__<<":"<<__LINE__<<" "<<#x<<"\n";abort();}} while(0)

namespace T118 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/line.hpp"
void test(){
Line<i64>a({0,0},{2,2}),b({0,2},{2,0});auto p=lineCross(a,b);CHECK(abs(p.x-1)<1e-12&&abs(p.y-1)<1e-12);CHECK(onLine(Point<i64>(1,1),a));CHECK(onLeft(Point<i64>(0,1),a));CHECK(abs(distancePL(Point<i64>(0,2),a)-sqrtl(2))<1e-12);
}
}

namespace T119 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/segment.hpp"
void test(){
for(int z=0;z<3000;z++){using P=Point<i64>;Line<i64>a(P(rnd(-5,5),rnd(-5,5)),P(rnd(-5,5),rnd(-5,5))),b(P(rnd(-5,5),rnd(-5,5)),P(rnd(-5,5),rnd(-5,5)));auto sign=[](__int128 x){return (x>0)-(x<0);};int x=sign(cross(a.b-a.a,b.a-a.a)),y=sign(cross(a.b-a.a,b.b-a.a)),u=sign(cross(b.b-b.a,a.a-b.a)),v=sign(cross(b.b-b.a,a.b-b.a));bool hit=(x*y<0&&u*v<0)||onSeg(a.a,b)||onSeg(a.b,b)||onSeg(b.a,a)||onSeg(b.b,a);auto [k,p,q]=segCross(a,b);CHECK((k!=0)==hit);if(k==2){CHECK(distancePS(p,Line<db>({db(a.a.x),db(a.a.y)},{db(a.b.x),db(a.b.y)}))<1e-10);CHECK(distancePS(q,Line<db>({db(b.a.x),db(b.a.y)},{db(b.b.x),db(b.b.y)}))<1e-10);}}
}
}

namespace T120 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/convex_hull.hpp"
void test(){
using P=Point<i64>;CHECK(convexHull(vector<P>{{1,1},{1,1}}).size()==1);auto h=convexHull(vector<P>{{0,0},{2,0},{2,2},{0,2},{1,1},{0,0}});CHECK(h.size()==4);CHECK(abs(polygonArea(h)-4)<1e-12);CHECK(convexHull(vector<P>{{0,0},{1,0},{2,0}}).size()==2);
}
}

namespace T121 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/point_in_polygon.hpp"
void test(){
vector<Point<i64>>p={{0,0},{4,0},{4,4},{2,2},{0,4}};CHECK(pointInPolygon(Point<i64>(1,1),p));CHECK(pointInPolygon(Point<i64>(0,2),p));CHECK(!pointInPolygon(Point<i64>(2,3),p));CHECK(!pointInPolygon(Point<i64>(-1,0),p));
}
}

namespace T122 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/closest_pair.hpp"
void test(){
for(int z=0;z<200;z++){vector<Point>a(rnd(2,100));for(auto&v:a)v={rnd(-100,100),rnd(-100,100)};__int128 best=(__int128(1)<<120);for(auto x:a)for(auto y:a){}for(int i=0;i<int(a.size());i++)for(int j=0;j<i;j++){__int128 x=__int128(a[i].x)-a[j].x,y=__int128(a[i].y)-a[j].y;best=min(best,x*x+y*y);}CHECK(closest2(a)==best);}CHECK(closest2({{1000000000000LL,0},{-1000000000000LL,0}})==__int128(4000000000000000000LL)*1000000);
}
}

namespace T123 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/rotating_calipers.hpp"
void test(){
auto hull=[](vector<Point<i64>> p){vector<T120::Point<i64>>a;for(auto v:p)a.push_back({v.x,v.y});auto b=T120::convexHull(a);vector<Point<i64>>c;for(auto v:b)c.push_back({v.x,v.y});return c;};for(int z=0;z<300;z++){vector<Point<i64>>a(rnd(0,40));for(auto&v:a)v={rnd(-100,100),rnd(-100,100)};auto h=hull(a);__int128 best=0;for(auto x:a)for(auto y:a)best=max(best,dist2(x,y));CHECK(diameter2(h)==best);}
}
}

namespace T124 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/circle.hpp"
void test(){
Circle c;CHECK(circumcircle({0,0},{2,0},{0,2},c));CHECK(abs(c.c.x-1)<1e-10&&abs(c.r-sqrtl(2))<1e-10);CHECK(!circumcircle({0,0},{1,0},{2,0},c));vector<Point>a;CHECK(circleCross({{0,0},1},{{2,0},1},a)==1);CHECK(circleCross({{0,0},1},{{1,0},1},a)==2);CHECK(circleCross({{0,0},1},{{0,0},1},a)==-1);CHECK(circleCross({{0,0},0},{{0,0},0},a)==1);
}
}

namespace T125 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/half_plane_intersection.hpp"
void test(){
for(int z=0;z<200;z++){ld l=rnd(-10,0),r=rnd(1,10),b=rnd(-10,0),t=rnd(1,10);vector<Line>a={Line({l,b},{r,b}),Line({r,b},{r,t}),Line({r,t},{l,t}),Line({l,t},{l,b}),Line({l-1,0},{l-1,-1})};shuffle(a.begin(),a.end(),rng);auto h=halfPlanes(a);ld s=0;for(int i=0;i<int(h.size());i++)s+=cross(h[i],h[(i+1)%h.size()]);CHECK(abs(abs(s)/2-(r-l)*(t-b))<1e-8);}for(int z=0;z<500;z++){vector<Point> p={{-10,-10},{10,-10},{10,10},{-10,10}};vector<Line>a;for(int i=0;i<4;i++)a.emplace_back(p[i],p[(i+1)%4]);for(int k=0;k<20;k++){Point v(rnd(-10,10),rnd(-10,10));ld len=hypotl(v.x,v.y);if(!len)continue;v=v*(1/len);ld c=-ld(rnd(1,20))/2;Point b=Point(-v.y,v.x)*c;Line l(b,b+v);a.push_back(l);vector<Point> q;for(int i=0;i<int(p.size());i++){Point x=p[i],y=p[(i+1)%p.size()];ld f=cross(l.v,x-l.p),g=cross(l.v,y-l.p);if(f>=-EPS)q.push_back(x);if((f>=-EPS)!=(g>=-EPS))q.push_back(x+(y-x)*(f/(f-g)));}p=q;}shuffle(a.begin(),a.end(),rng);auto h=halfPlanes(a);auto area=[](vector<Point>p){ld ans=0;for(int i=0;i<int(p.size());i++)ans+=cross(p[i],p[(i+1)%p.size()]);return fabsl(ans)/2;};CHECK(fabsl(area(p)-area(h))<1e-7);for(auto x:h)for(auto l:a)CHECK(cross(l.v,x-l.p)>-1e-8);}vector<Line>a={Line({0,0},{1,0}),Line({1,0},{1,1}),Line({1,1},{0,1}),Line({0,1},{0,0}),Line({0,2},{1,2})};CHECK(halfPlanes(a).empty());
}
}

namespace T126 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/minkowski_sum.hpp"
void test(){
auto hull=[](vector<Point<i64>> p){vector<T120::Point<i64>>a;for(auto v:p)a.push_back({v.x,v.y});auto b=T120::convexHull(a);vector<Point<i64>>c;for(auto v:b)c.push_back({v.x,v.y});return c;};using P=Point<i64>;for(int z=0;z<200;z++){vector<P>a(rnd(1,20)),b(rnd(1,20));for(auto&v:a)v={rnd(-10,10),rnd(-10,10)};for(auto&v:b)v={rnd(-10,10),rnd(-10,10)};a=hull(a);b=hull(b);vector<P>c;for(auto x:a)for(auto y:b)c.push_back(x+y);auto x=hull(c),y=minkowskiSum(a,b);auto cmp=[](P a,P b){return tie(a.x,a.y)<tie(b.x,b.y);};sort(x.begin(),x.end(),cmp);sort(y.begin(),y.end(),cmp);CHECK(x==y);}
}
}

namespace T127 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/rectangle_union.hpp"
void test(){
for(int z=0;z<200;z++){vector<array<i64,4>>a;bool grid[20][20]{};for(int k=0;k<10;k++){int x=rnd(0,9),y=rnd(0,9),r=rnd(x,10),t=rnd(y,10);a.push_back({x,y,r,t});for(int i=x;i<r;i++)for(int j=y;j<t;j++)grid[i][j]=1;}i64 area=0;for(auto&r:grid)for(bool x:r)area+=x;CHECK(rectArea(a)==area);}
}
}

namespace T129 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/mo.hpp"
void test(){
for(int z=0;z<200;z++){int n=30;vector<int>a(n+1);for(int&x:a)x=rnd(-20,20);vector<pair<int,int>>q;vector<int>b;for(int k=0;k<50;k++){int l=rnd(1,n),r=rnd(l,n);q.push_back({l,r});b.push_back(set<int>(a.begin()+l,a.begin()+r+1).size());}CHECK(moDistinct(a,q)==b);}
}
}

namespace T130 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/cdq.hpp"
void test(){
for(int z=0;z<200;z++){vector<array<int,3>>a(rnd(0,80));for(auto&v:a)for(int&x:v)x=rnd(-5,5);auto b=dominance(a);for(int i=0;i<int(a.size());i++){int k=-1;for(auto v:a)k+=v[0]<=a[i][0]&&v[1]<=a[i][1]&&v[2]<=a[i][2];CHECK(b[i]==k);}}
}
}

namespace T131 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/parallel_binary_search.hpp"
void test(){
for(int z=0;z<100;z++){int n=20;vector<int>a(n+1);vector<KthOffline::Event>e;for(int i=1;i<=n;i++)a[i]=rnd(-20,20),e.push_back({0,i,a[i],1,0,0,0,0});vector<int>b;for(int k=0;k<100;k++)if(rnd(0,1)){int i=rnd(1,n),v=rnd(-20,20);e.push_back({0,i,a[i],-1,0,0,0,0});a[i]=v;e.push_back({0,i,v,1,0,0,0,0});}else{int l=rnd(1,n),r=rnd(l,n),t=rnd(1,r-l+1);auto v=vector<int>(a.begin()+l,a.begin()+r+1);sort(v.begin(),v.end());e.push_back({1,0,0,0,l,r,t,int(b.size())});b.push_back(v[t-1]);}CHECK(KthOffline().solve(n,e,b.size())==b);}
}
}

namespace T132 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/offline_connectivity.hpp"
void test(){
for(int z=0;z<100;z++){int n=10,q=30;OfflineConn s(n,q);vector<array<int,4>>e;for(int k=0;k<30;k++){int l=rnd(1,q),r=rnd(l,q),u=rnd(1,n),v=rnd(1,n);s.add(l,r,u,v);e.push_back({l,r,u,v});}vector<pair<int,int>>a(q+1);for(int t=1;t<=q;t++)a[t]={rnd(1,n),rnd(1,n)};auto b=s.solve(a);for(int t=1;t<=q;t++){vector<vector<int>>g(n+1);for(auto [l,r,u,v]:e)if(l<=t&&t<=r)g[u].push_back(v),g[v].push_back(u);vector<int>vis(n+1);queue<int>st;st.push(a[t].first);vis[a[t].first]=1;while(!st.empty()){int u=st.front();st.pop();for(int v:g[u])if(!vis[v])vis[v]=1,st.push(v);}CHECK(b[t]==vis[a[t].second]);}}
}
}
int main(){
T118::test(); cout<<"PASS line "<<checks<<"\n";
T119::test(); cout<<"PASS segment "<<checks<<"\n";
T120::test(); cout<<"PASS convex_hull "<<checks<<"\n";
T121::test(); cout<<"PASS point_in_polygon "<<checks<<"\n";
T122::test(); cout<<"PASS closest_pair "<<checks<<"\n";
T123::test(); cout<<"PASS rotating_calipers "<<checks<<"\n";
T124::test(); cout<<"PASS circle "<<checks<<"\n";
T125::test(); cout<<"PASS half_plane_intersection "<<checks<<"\n";
T126::test(); cout<<"PASS minkowski_sum "<<checks<<"\n";
T127::test(); cout<<"PASS rectangle_union "<<checks<<"\n";
T129::test(); cout<<"PASS mo "<<checks<<"\n";
T130::test(); cout<<"PASS cdq "<<checks<<"\n";
T131::test(); cout<<"PASS parallel_binary_search "<<checks<<"\n";
T132::test(); cout<<"PASS offline_connectivity "<<checks<<"\n";
}
