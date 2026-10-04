#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using i64=long long;
mt19937 rng(712367);
int rnd(int l,int r){return uniform_int_distribution<int>(l,r)(rng);}
long long checks=0;
#define CHECK(x) do {++checks;if(!(x)){cerr<<"FAIL "<<__FILE__<<":"<<__LINE__<<" "<<#x<<"\n";abort();}} while(0)

namespace T61 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/lis.hpp"
void test(){
for(int z=0;z<200;z++){vector<int>a(rnd(0,40));for(int&x:a)x=rnd(-5,5);for(bool strict:{false,true}){vector<int>d(a.size(),1);int ans=0;for(int i=0;i<int(a.size());i++){for(int j=0;j<i;j++)if(strict?a[j]<a[i]:a[j]<=a[i])d[i]=max(d[i],d[j]+1);ans=max(ans,d[i]);}CHECK(lisLength(a,strict)==ans);}}
}
}

namespace T62 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/multi_knapsack.hpp"
void test(){
for(int z=0;z<200;z++){int n=6,V=30;vector<int>w(n+1),m(n+1);vector<i64>v(n+1),d(V+1);for(int i=1;i<=n;i++)w[i]=rnd(1,40),m[i]=rnd(0,6),v[i]=rnd(-5,20);for(int i=1;i<=n;i++){auto a=d;for(int j=0;j<=V;j++)for(int k=0;k<=m[i]&&k*w[i]<=j;k++)d[j]=max(d[j],a[j-k*w[i]]+k*v[i]);}CHECK(multiKnapsack(n,V,w,v,m)==d[V]);}
}
}

namespace T78 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/modint.hpp"
void test(){
using M=MInt<2147483647>;CHECK((M(2147483646)+M(2147483646)).val()==2147483645);CHECK((M(-1)*M(-1)).val()==1);CHECK((M(13)/M(13)).val()==1);
}
}

namespace T79 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/exgcd_crt.hpp"
void test(){
for(int m=1;m<=20;m++)for(int n=1;n<=20;n++)for(int z=0;z<5;z++){i64 a=rnd(-30,30),b=rnd(-30,30),r,M;int x=crtMerge(a,m,b,n,r,M);i64 best=-1;for(int k=0;k<lcm(m,n);k++)if((k-a)%m==0&&(k-b)%n==0){best=k;break;}CHECK(x==(best<0?0:1));if(x==1)CHECK(r==best&&M==lcm(m,n));}i64 a,b;CHECK(crtMerge(0,LLONG_MAX,0,LLONG_MAX-1,a,b)==-1);CHECK(invMod(LLONG_MAX-1,LLONG_MAX,a)&&a==LLONG_MAX-1);
}
}

namespace T80 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/combination.hpp"
void test(){
Combination s(100,101);vector<vector<int>>c(101,vector<int>(101));for(int n=0;n<=100;n++){c[n][0]=1;for(int k=1;k<=n;k++)c[n][k]=(c[n-1][k-1]+c[n-1][k])%101;for(int k=0;k<=n;k++)CHECK(s.C(n,k)==c[n][k]);}
}
}

namespace T81 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/lucas.hpp"
void test(){
for(int p:{2,3,5,7}){Lucas s(p);vector<vector<int>>c(101,vector<int>(101));for(int n=0;n<=100;n++){c[n][0]=1;for(int k=1;k<=n;k++)c[n][k]=(c[n-1][k-1]+c[n-1][k])%p;for(int k=0;k<=n;k++)CHECK(s.C(n,k)==c[n][k]);}}
}
}

namespace T82 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/lagrange.hpp"
void test(){
for(int z=0;z<100;z++){int p=101,n=rnd(0,10);vector<int>a(n+1),y(n+1);for(int&x:a)x=rnd(0,p-1);auto eval=[&](i64 x){x=(x%p+p)%p;i64 r=0;for(int i=n;i>=0;i--)r=(r*x+a[i])%p;return int(r);};for(int i=0;i<=n;i++)y[i]=eval(i);for(int x=-150;x<150;x++)CHECK(lagrange(y,x,p)==eval(x));}for(int z=0;z<100;z++){int P=2147483647;vector<int>a(8),y(8);for(int&x:a)x=rnd(0,P-1);auto f=[&](i64 x){x=(x%P+P)%P;i64 v=0;for(int i=7;i>=0;i--)v=(v*x+a[i])%P;return int(v);};for(int i=0;i<8;i++)y[i]=f(i);for(int x=-30;x<60;x++)CHECK(lagrange(y,x,P)==f(x));}
}
}

namespace T83 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/linear_sieve.hpp"
void test(){
LinearSieve s(2000);for(int n=1;n<=2000;n++){int phi=0;for(int k=1;k<=n;k++)phi+=gcd(k,n)==1;int x=n,mu=1;for(int p=2;p*p<=x;p++)if(x%p==0){int c=0;while(x%p==0)x/=p,c++;mu=c>1?0:-mu;}if(x>1)mu=-mu;CHECK(s.phi[n]==phi&&s.mu[n]==mu);}
}
}

namespace T84 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/mobius_phi.hpp"
void test(){
MobiusPhi s(2000);for(int n=1;n<=2000;n++){int phi=0;for(int k=1;k<=n;k++)phi+=gcd(k,n)==1;int x=n,mu=1;for(int p=2;p*p<=x;p++)if(x%p==0){int c=0;while(x%p==0)x/=p,c++;mu=c>1?0:-mu;}if(x>1)mu=-mu;CHECK(s.phi[n]==phi&&s.mu[n]==mu);}
}
}

namespace T85 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/miller_rabin.hpp"
void test(){
for(int n=0;n<10000;n++){bool p=n>=2;for(int k=2;k*k<=n;k++)if(n%k==0)p=false;CHECK(isPrime(n)==p);}CHECK(!isPrime(341550071728321ULL));CHECK(isPrime(18446744073709551557ULL));
}
}

namespace T86 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/pollard_rho.hpp"
void test(){
for(i64 n:{1LL,2LL,360LL,1000000007LL*1000000009LL,9223372036854775783LL}){auto a=PollardRho::factorize(n,712367);__int128 prod=1;for(auto p:a){CHECK(PollardRho::isPrime(p));prod*=p;}CHECK(prod==n);}
}
}

namespace T87 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/division_blocks.hpp"
void test(){
for(i64 n=0;n<=1000;n++){i64 a=0;for(int k=1;k<=n;k++)a+=n/k;CHECK(sumFloorDiv(n,n)==a);}
}
}

namespace T88 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/floor_sum.hpp"
void test(){
for(int z=0;z<5000;z++){int n=rnd(0,20),a=rnd(-30,30),b=rnd(-30,30),c=rnd(1,20);i64 f=0,g=0,h=0;for(int i=0;i<=n;i++){i64 x=i*a+b,q=x/c;if(x<0&&x%c)q--;f+=q;g+=i*q;h+=q*q;}auto x=floorSum(n,a,b,c);CHECK(x.f==f&&x.g==g&&x.h==h);}
}
}

namespace T89 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/bsgs.hpp"
void test(){
for(i64 m=1;m<=40;m++)for(i64 a=-1;a<=m;a++)for(i64 b=0;b<m;b++){set<i64>vis;i64 x=1%m,ans=-1;for(int k=0;!vis.count(x);k++){vis.insert(x);if(x==b){ans=k;break;}x=(__int128(x)*((a%m+m)%m))%m;}CHECK(BSGS::solve(a,b,m)==ans);}
}
}

namespace T90 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/matrix.hpp"
void test(){
Matrix a(2,2);a(1,1)=a(1,2)=a(2,1)=1;vector<int>f(40);f[1]=1;for(int i=2;i<40;i++)f[i]=(f[i-1]+f[i-2])%MOD;for(int k=0;k<35;k++){auto r=power(a,k)*vector<int>{0,1,0};CHECK(r[2]==f[k]);}Matrix b(2,3),c(3,1);b(1,3)=7;c(3,1)=9;CHECK((b*c)(1,1)==63);
}
}

namespace T91 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/dujiao_sieve.hpp"
void test(){
DuJiaoSieve s(30);vector<int>phi(10001),mu(10001,1);iota(phi.begin(),phi.end(),0);for(int p=2;p<=10000;p++)if(phi[p]==p){for(int j=p;j<=10000;j+=p)phi[j]=phi[j]/p*(p-1),mu[j]=-mu[j];if(p*p<=10000)for(int j=p*p;j<=10000;j+=p*p)mu[j]=0;}i64 a=0,b=0;for(int n=1;n<=10000;n++){a+=phi[n];b+=mu[n];if(n<300||n%97==0){auto v=s.get(n);CHECK(v.first==a&&v.second==b);CHECK(s.get(n)==v);}}CHECK(s.get(0).first==0);
}
}

namespace T92 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/min25_sieve.hpp"
void test(){
const int P=1000000007;i64 sum=1;for(int n=1;n<=500;n++){if(n>1){int x=n;i64 val=1;for(int p=2;p*p<=x;p++)if(x%p==0){i64 pe=1;while(x%p==0)x/=p,pe*=p;val=val*pe%P*(pe-1)%P;}if(x>1)val=val*x%P*(x-1)%P;sum=(sum+val)%P;}CHECK(Min25Sieve(n,P).solve()==sum);}
}
}

namespace T99 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/fft.hpp"
void test(){
for(int z=0;z<100;z++){vector<int>a(rnd(0,100)),b(rnd(0,100));for(int&x:a)x=rnd(-100,100);for(int&x:b)x=rnd(-100,100);vector<i64>c(a.empty()||b.empty()?0:a.size()+b.size()-1);for(int i=0;i<int(a.size());i++)for(int j=0;j<int(b.size());j++)c[i+j]+=1LL*a[i]*b[j];CHECK(convolutionFft(a,b)==c);}
}
}
int main(){
T61::test(); cout<<"PASS lis "<<checks<<"\n";
T62::test(); cout<<"PASS multi_knapsack "<<checks<<"\n";
T78::test(); cout<<"PASS modint "<<checks<<"\n";
T79::test(); cout<<"PASS exgcd_crt "<<checks<<"\n";
T80::test(); cout<<"PASS combination "<<checks<<"\n";
T81::test(); cout<<"PASS lucas "<<checks<<"\n";
T82::test(); cout<<"PASS lagrange "<<checks<<"\n";
T83::test(); cout<<"PASS linear_sieve "<<checks<<"\n";
T84::test(); cout<<"PASS mobius_phi "<<checks<<"\n";
T85::test(); cout<<"PASS miller_rabin "<<checks<<"\n";
T86::test(); cout<<"PASS pollard_rho "<<checks<<"\n";
T87::test(); cout<<"PASS division_blocks "<<checks<<"\n";
T88::test(); cout<<"PASS floor_sum "<<checks<<"\n";
T89::test(); cout<<"PASS bsgs "<<checks<<"\n";
T90::test(); cout<<"PASS matrix "<<checks<<"\n";
T91::test(); cout<<"PASS dujiao_sieve "<<checks<<"\n";
T92::test(); cout<<"PASS min25_sieve "<<checks<<"\n";
T99::test(); cout<<"PASS fft "<<checks<<"\n";
}
