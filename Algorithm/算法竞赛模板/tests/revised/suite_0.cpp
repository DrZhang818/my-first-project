#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using i64=long long;
mt19937 rng(712367);
int rnd(int l,int r){return uniform_int_distribution<int>(l,r)(rng);}
long long checks=0;
#define CHECK(x) do {++checks;if(!(x)){cerr<<"FAIL "<<__FILE__<<":"<<__LINE__<<" "<<#x<<"\n";abort();}} while(0)

namespace T0 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/dsu.hpp"
void test(){
DSU d(10); CHECK(d.merge(1,2)); CHECK(!d.merge(2,1)); CHECK(d.size(2)==2); CHECK(d.groups()==9);
}
}

namespace T1 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/rollback_dsu.hpp"
void test(){
UndoDSU d(10); int s=d.snapshot(); d.merge(1,2); d.merge(2,3); CHECK(d.size(3)==3); d.rollback(s); CHECK(!d.same(1,3)); CHECK(d.groups()==10);
}
}

namespace T2 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/weighted_dsu.hpp"
void test(){
WeightDSU<> d(20); for(int i=1;i<20;i++) CHECK(d.merge(i,i+1,3)); CHECK(d.diff(1,20)==57); CHECK(!d.merge(1,20,58)); CHECK(d.merge(20,1,-57));
}
}

namespace T3 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/successor_dsu.hpp"
void test(){
NextDSU d(200000); for(int i=1;i<=200000;i++) d.erase(i); CHECK(d.next(1)==200001);
}
}

namespace T4 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/fenwick.hpp"
void test(){
for(int n=1;n<=40;n++) {BIT<> b(n); vector<i64>a(n+1); for(int z=0;z<100;z++){int p=rnd(1,n),v=rnd(0,9);b.add(p,v);a[p]+=v;int l=rnd(1,n),r=rnd(l,n);CHECK(b.query(l,r)==accumulate(a.begin()+l,a.begin()+r+1,0LL));i64 sum=accumulate(a.begin(),a.end(),0LL),k=rnd(1,int(sum+1));int x=1; i64 s=0;while(x<=n && s+a[x]<k)s+=a[x++];CHECK(b.select(k)==x);}}
}
}

namespace T5 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/sparse_table.hpp"
void test(){
for(int n=1;n<=50;n++){vector<int>a(n+1);for(int&i:a)i=rnd(-20,20);auto f=[](int x,int y){return min(x,y);};ST<int,decltype(f)>s(a,f);for(int l=1;l<=n;l++)for(int r=l;r<=n;r++)CHECK(s.query(l,r)==*min_element(a.begin()+l,a.begin()+r+1));}
}
}

namespace T6 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/segment_tree.hpp"
void test(){
struct Info {i64 s=0;Info(i64 s=0):s(s){} Info operator+(Info b)const{return Info(s+b.s);}};
for(int n=1;n<=35;n++){vector<Info>a(n+1);vector<i64>b(n+1);for(int i=1;i<=n;i++)a[i]=b[i]=rnd(0,9);Seg<Info>s(a);for(int z=0;z<100;z++){int l=rnd(1,n),r=rnd(l,n);i64 sum=accumulate(b.begin()+l,b.begin()+r+1,0LL);CHECK(s.query(l,r).s==sum);i64 k=rnd(1,int(sum+1)),cur=0;int p=-1;for(int i=l;i<=r;i++){cur+=b[i];if(cur>=k){p=i;break;}}CHECK(s.first(l,r,[&](Info x){return x.s>=k;})==p);int x=rnd(1,n);b[x]=rnd(0,9);s.modify(x,Info(b[x]));}}
struct Str {string s;Str(string x=""):s(x){} Str operator+(Str b)const{return Str(s+b.s);}};vector<Str>a(8);for(int i=1;i<8;i++)a[i]=Str(string(1,'a'+i));Seg<Str>s(a);CHECK(s.query(2,6).s=="cdefg");
}
}

namespace T7 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/lazy_segment_tree.hpp"
void test(){
struct Tag {i64 mul=1,add=0;void apply(Tag b){mul*=b.mul;add=add*b.mul+b.add;}};struct Info {i64 sum=0;int len=0;Info(i64 s=0,int n=0):sum(s),len(n){}void apply(Tag b){sum=sum*b.mul+b.add*len;}Info operator+(Info b)const{return Info(sum+b.sum,len+b.len);}};
for(int n=1;n<=25;n++){vector<Info>a(n+1);vector<i64>b(n+1);for(int i=1;i<=n;i++)a[i]=Info(b[i]=rnd(0,9),1);LazySeg<Info,Tag>s(a);for(int z=0;z<50;z++){int l=rnd(1,n),r=rnd(l,n);Tag t;t.mul=rnd(0,1);t.add=rnd(0,5);s.apply(l,r,t);for(int i=l;i<=r;i++)b[i]=b[i]*t.mul+t.add;CHECK(s.query(l,r).sum==accumulate(b.begin()+l,b.begin()+r+1,0LL));}}
}
}

namespace T8 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/persistent_segment_tree.hpp"
void test(){
struct Info {int s=0;Info(int s=0):s(s){}void apply(Info b){s+=b.s;}Info operator+(Info b)const{return Info(s+b.s);}Info operator-(Info b)const{return Info(s-b.s);}};
PST<Info>s(20);vector<int>rt(1,0),a;for(int z=0;z<200;z++){int x=rnd(1,20);a.push_back(x);rt.push_back(s.modify(rt.back(),x,Info(1)));int l=rnd(0,z),r=rnd(l,z+1),v=rnd(1,20);int cnt=0;for(int i=l;i<r;i++)cnt+=a[i]<=v;CHECK(s.query(rt[l],rt[r],1,v).s==cnt);vector<int>b(a.begin()+l,a.begin()+r);sort(b.begin(),b.end());for(int k=1;k<=int(b.size());k++)CHECK(s.first(rt[l],rt[r],1,20,[&](Info t){return t.s>=k;})==b[k-1]);}
}
}

namespace T9 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/dynamic_segment_tree.hpp"
void test(){
struct Info {i64 s=0;Info(i64 s=0):s(s){}Info operator+(Info b)const{return Info(s+b.s);}};DynSeg<Info>s(-50,50);int rt=0;map<int,i64>a;for(int z=0;z<500;z++){int x=rnd(-50,50);a[x]=rnd(-30,30);s.modify(rt,x,Info(a[x]));int l=rnd(-50,50),r=rnd(l,50);i64 sum=0;for(auto [p,v]:a)if(l<=p&&p<=r)sum+=v;CHECK(s.query(rt,l,r).s==sum);}
}
}

namespace T10 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/segment_tree_beats.hpp"
void test(){
for(int n=1;n<=30;n++){vector<i64>a(n+1);for(int i=1;i<=n;i++)a[i]=rnd(-50,50);Beats s(a);for(int z=0;z<300;z++){int l=rnd(1,n),r=rnd(l,n),x=rnd(-100,100);s.chmin(l,r,x);for(int i=l;i<=r;i++)a[i]=min(a[i],i64(x));CHECK(s.sum(l,r)==accumulate(a.begin()+l,a.begin()+r+1,0LL));CHECK(s.maxi(l,r)==*max_element(a.begin()+l,a.begin()+r+1));}}Beats s(vector<i64>{0,0});s.chmin(1,1,LLONG_MIN);CHECK(s.maxi(1,1)==LLONG_MIN);
}
}

namespace T11 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/fhq_treap.hpp"
void test(){
FHQ s;multiset<int>a;for(int z=0;z<2000;z++){int x=rnd(-20,20);if(rnd(0,1)){a.insert(x);s.insert(x);}else{auto it=a.find(x);bool ok=it!=a.end();CHECK(s.erase(x)==ok);if(ok)a.erase(it);}CHECK(s.size()==int(a.size()));CHECK(s.rank(x)==int(distance(a.begin(),a.lower_bound(x)))+1);int v;auto it=a.lower_bound(x);CHECK(s.prev(x,v)==(it!=a.begin()));if(it!=a.begin())CHECK(v==*prev(it));it=a.upper_bound(x);CHECK(s.next(x,v)==(it!=a.end()));if(it!=a.end())CHECK(v==*it);int k=0;for(int v:a)CHECK(s.kth(++k)==v);}
}
}

namespace T12 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/implicit_treap.hpp"
void test(){
struct Policy {using Val=i64;using Info=i64;using Tag=i64;static Info identity(){return 0;}static Tag tagIdentity(){return 0;}static bool tagEmpty(Tag t){return t==0;}static Info make(Val v){return v;}static Info merge(Info a,Info b){return a+b;}static void apply(Val&v,Info&i,int n,Tag t){v+=t;i+=n*t;}static void compose(Tag&a,Tag b){a+=b;}static void reverseInfo(Info&){} };
Treap<Policy>s;vector<i64>a(20);iota(a.begin(),a.end(),0);int rt=s.build(a);for(int z=0;z<200;z++){int l=rnd(1,a.size()),r=rnd(l,a.size());if(rnd(0,1)){s.rangeReverse(rt,l,r);reverse(a.begin()+l-1,a.begin()+r);}else{int d=rnd(-5,5);s.apply(rt,l,r,d);for(int i=l-1;i<r;i++)a[i]+=d;}CHECK(s.query(rt,l,r)==accumulate(a.begin()+l-1,a.begin()+r,0LL));for(int i=0;i<int(a.size());i++)CHECK(s.tr[s.kth(rt,i+1)].val==a[i]);}int mid=s.erase(rt,3,5);a.erase(a.begin()+2,a.begin()+5);s.insert(rt,0,mid);CHECK(s.size(rt)==20);
}
}

namespace T13 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/ordered_multiset.hpp"
void test(){
OrderedSet<int>s;multiset<int>a;for(int z=0;z<500;z++){int x=rnd(-10,10);if(rnd(0,1)){s.insert(x);a.insert(x);}else{auto it=a.find(x);CHECK(s.erase(x)==(it!=a.end()));if(it!=a.end())a.erase(it);}CHECK(s.count(x)==int(a.count(x)));CHECK(s.orderOfKey(x)==int(distance(a.begin(),a.lower_bound(x))));int k=0,v;for(int y:a){CHECK(s.kth(++k,v));CHECK(v==y);}CHECK(!s.kth(0,v));}
}
}

namespace T14 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/li_chao.hpp"
void test(){
LiChao s(-100,100);vector<pair<i64,i64>>a;for(int z=0;z<300;z++){i64 k=rnd(-100,100),b=rnd(-100,100);s.addLine(k,b);a.push_back({k,b});for(int x=-100;x<=100;x++){__int128 best=LiChao::inf;for(auto [k,b]:a)best=min(best,__int128(k)*x+b);CHECK(s.query(x)==best);}}
}
}

namespace T15 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/convex_hull_dp.hpp"
void test(){
CHT s;vector<CHT::Point>a;for(int x=-20;x<=20;x++){CHT::Point p{x,rnd(-100,100)};s.addPoint(p);a.push_back(p);for(int z=0;z<10;z++){CHT::Point q{rnd(-20,20),rnd(1,10)};__int128 b=(__int128(1)<<120);for(auto p:a)b=min(b,CHT::dot(p,q));CHECK(s.query(q)==b);}}
}
}

namespace T16 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/cartesian_tree.hpp"
void test(){
for(int n=0;n<=100;n++){vector<int>a(n+1);for(int&i:a)i=rnd(-5,5);Cartesian<int>s(a);vector<int>v;function<void(int)>dfs=[&](int u){if(!u)return;if(s.left[u])CHECK(a[u]<=a[s.left[u]]);if(s.right[u])CHECK(a[u]<=a[s.right[u]]);dfs(s.left[u]);v.push_back(u);dfs(s.right[u]);};dfs(s.root);CHECK(v.size()==size_t(n));for(int i=1;i<=n;i++)CHECK(v[i-1]==i);}
}
}

namespace T17 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/link_cut_tree.hpp"
void test(){
int n=12;LCT s(n);vector<set<int>>g(n+1);vector<i64>a(n+1);auto path=[&](int u,int v){vector<int>p(n+1,-1);queue<int>q;q.push(u);p[u]=0;while(!q.empty()){int x=q.front();q.pop();for(int y:g[x])if(p[y]<0)p[y]=x,q.push(y);}vector<int>b;if(p[v]<0)return b;for(int x=v;x;x=p[x])b.push_back(x);return b;};for(int z=0;z<1500;z++){int u=rnd(1,n),v=rnd(1,n),op=rnd(0,3);auto b=path(u,v);if(op==0){bool ok=u!=v&&b.empty();CHECK(s.link(u,v)==ok);if(ok)g[u].insert(v),g[v].insert(u);}if(op==1){bool ok=g[u].count(v);CHECK(s.cut(u,v)==ok);if(ok)g[u].erase(v),g[v].erase(u);}if(op==2)a[u]=rnd(0,1023),s.setValue(u,a[u]);CHECK(s.connected(u,v)==!b.empty() || op==0 || op==1);b=path(u,v);if(!b.empty()){i64 val=0;for(int x:b)val^=a[x];CHECK(s.pathXor(u,v)==val);}}
}
}
int main(){
T0::test(); cout<<"PASS dsu "<<checks<<"\n";
T1::test(); cout<<"PASS rollback_dsu "<<checks<<"\n";
T2::test(); cout<<"PASS weighted_dsu "<<checks<<"\n";
T3::test(); cout<<"PASS successor_dsu "<<checks<<"\n";
T4::test(); cout<<"PASS fenwick "<<checks<<"\n";
T5::test(); cout<<"PASS sparse_table "<<checks<<"\n";
T6::test(); cout<<"PASS segment_tree "<<checks<<"\n";
T7::test(); cout<<"PASS lazy_segment_tree "<<checks<<"\n";
T8::test(); cout<<"PASS persistent_segment_tree "<<checks<<"\n";
T9::test(); cout<<"PASS dynamic_segment_tree "<<checks<<"\n";
T10::test(); cout<<"PASS segment_tree_beats "<<checks<<"\n";
T11::test(); cout<<"PASS fhq_treap "<<checks<<"\n";
T12::test(); cout<<"PASS implicit_treap "<<checks<<"\n";
T13::test(); cout<<"PASS ordered_multiset "<<checks<<"\n";
T14::test(); cout<<"PASS li_chao "<<checks<<"\n";
T15::test(); cout<<"PASS convex_hull_dp "<<checks<<"\n";
T16::test(); cout<<"PASS cartesian_tree "<<checks<<"\n";
T17::test(); cout<<"PASS link_cut_tree "<<checks<<"\n";
}
