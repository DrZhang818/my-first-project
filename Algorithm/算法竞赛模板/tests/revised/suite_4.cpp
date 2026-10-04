#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using i64=long long;
mt19937 rng(712367);
int rnd(int l,int r){return uniform_int_distribution<int>(l,r)(rng);}
long long checks=0;
#define CHECK(x) do {++checks;if(!(x)){cerr<<"FAIL "<<__FILE__<<":"<<__LINE__<<" "<<#x<<"\n";abort();}} while(0)

namespace T100 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/ntt.hpp"
void test(){
for(int z=0;z<50;z++){vector<int>a(rnd(70,120)),b(rnd(70,120));for(int&x:a)x=rnd(-100,100);for(int&x:b)x=rnd(-100,100);vector<int>c(a.size()+b.size()-1);for(int i=0;i<int(a.size());i++)for(int j=0;j<int(b.size());j++)c[i+j]=(c[i+j]+1LL*normalize(a[i])*normalize(b[j]))%MOD;CHECK(convolution(a,b)==c);int k=rnd(1,80);c.resize(k);CHECK(convolutionTrunc(a,b,k)==c);}
}
}

namespace T101 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/fwt.hpp"
void test(){
for(int z=0;z<100;z++){int n=1<<rnd(0,6);vector<int>a(n),b(n);for(int&x:a)x=rnd(-100,100);for(int&x:b)x=rnd(-100,100);for(int k=0;k<3;k++){vector<int>c(n);for(int i=0;i<n;i++)for(int j=0;j<n;j++){int v=k==0?(i|j):k==1?(i&j):(i^j);c[v]=(c[v]+1LL*((a[i]+P)%P)*((b[j]+P)%P))%P;}CHECK((k==0?convOr(a,b):k==1?convAnd(a,b):convXor(a,b))==c);}}
}
}

namespace T102 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/fps.hpp"
void test(){
for(int z=0;z<25;z++){int n=rnd(65,160);vector<int>a(n);a[0]=1;for(int i=1;i<n;i++)a[i]=rnd(0,1000);auto b=polyInv(a,n);vector<int>c(n);for(int i=0;i<n;i++)for(int j=0;i+j<n;j++)c[i+j]=(c[i+j]+1LL*a[i]*b[j])%FPS_MOD;CHECK(c[0]==1);for(int i=1;i<n;i++)CHECK(c[i]==0);CHECK(polyExp(polyLog(a,n),n)==a);auto d=a;d[0]=0;CHECK(polyLog(polyExp(d,n),n)==d);}
}
}

namespace T103 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/gauss.hpp"
void test(){
for(int z=0;z<500;z++){int n=rnd(1,5),m=rnd(1,4),p=3;vector<vector<int>>a(n+1,vector<int>(m+2));for(int i=1;i<=n;i++)for(int j=1;j<=m+1;j++)a[i][j]=rnd(0,p-1);auto b=a;vector<int>w;int r=gaussMod(b,p,w);bool good=true;for(int i=r+1;i<=n;i++)if(b[i][m+1])good=false;bool ref=false;int lim=1;for(int i=0;i<m;i++)lim*=p;for(int mask=0;mask<lim;mask++){int x=mask;vector<int>v(m+1);for(int j=1;j<=m;j++)v[j]=x%p,x/=p;bool ok=true;for(int i=1;i<=n;i++){int s=0;for(int j=1;j<=m;j++)s+=a[i][j]*v[j];ok&=s%p==a[i][m+1];}ref|=ok;}CHECK(good==ref);if(good){vector<int>v(m+1);for(int j=1;j<=m;j++)if(w[j])v[j]=b[w[j]][m+1];for(int i=1;i<=n;i++){int s=0;for(int j=1;j<=m;j++)s+=a[i][j]*v[j];CHECK(s%p==a[i][m+1]);}}}vector<vector<double>>a={{},{0,1,2,5},{0,2,-1,0}};vector<int>w;CHECK(gaussDouble(a,w)==2);CHECK(abs(a[w[1]][3]-1)<1e-8);
}
}

namespace T104 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/xor_basis.hpp"
void test(){
for(int z=0;z<200;z++){int n=rnd(0,10);vector<u64>a(n);XorBasis s;for(auto&x:a)x=rnd(0,1023),s.insert(x);set<u64>b;for(int mask=1;mask<(1<<n);mask++){u64 v=0;for(int i=0;i<n;i++)if(mask>>i&1)v^=a[i];b.insert(v);}u64 v;CHECK(s.minXor(v)==!b.empty());if(!b.empty())CHECK(v==*b.begin());int k=0;for(u64 x:b){CHECK(s.kth(++k,v));CHECK(v==x);}CHECK(!s.kth(++k,v));CHECK(s.maxXor()==(b.empty()?0:*b.rbegin()));for(int i=0;i<1024;i++)CHECK(s.decompose(i)==(i==0||b.count(i)));}XorBasis s;s.insert(ULLONG_MAX);u64 v;CHECK(s.kth(1,v)&&v==ULLONG_MAX);
}
}

namespace T105 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/xor_system.hpp"
void test(){
for(int z=0;z<300;z++){int n=5,m=4;XorLinearSystem<32>s(n,m,1);vector<vector<int>>a(n,vector<int>(m+1));for(int i=0;i<n;i++){for(int j=0;j<m;j++)a[i][j]=rnd(0,1),s.setCoeff(i,j,a[i][j]);a[i][m]=rnd(0,1);s.setRhs(i,0,a[i][m]);}bool ok=false;for(int mask=0;mask<(1<<m);mask++){bool good=true;for(auto v:a){int x=0;for(int j=0;j<m;j++)x^=v[j]&(mask>>j&1);good&=x==v[m];}ok|=good;}CHECK(s.solve()==ok);if(ok){auto x=s.answer();for(auto v:a){int r=0;for(int j=0;j<m;j++)r^=v[j]&x[j][0];CHECK(r==v[m]);}}}
}
}

namespace T106 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/kmp.hpp"
void test(){
for(int z=0;z<300;z++){string s(rnd(0,30),'a'),p(rnd(0,10),'a');for(char&c:s)c+=rnd(0,2);for(char&c:p)c+=rnd(0,2);vector<int>a;if(!p.empty())for(int i=0;i+int(p.size())<=int(s.size());i++)if(s.substr(i,p.size())==p)a.push_back(i+1);CHECK(kmpMatch(s,p)==a);}
}
}

namespace T107 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/z_function.hpp"
void test(){
for(int z=0;z<300;z++){string s(rnd(0,30),'a'),p(rnd(0,10),'a');for(char&c:s)c+=rnd(0,2);for(char&c:p)c+=rnd(0,2);auto a=zFunction(s),b=exKmp(s,p);for(int i=0;i<int(s.size());i++){int k=0;while(i+k<int(s.size())&&s[k]==s[i+k])k++;CHECK(a[i+1]==k);k=0;while(k<int(p.size())&&i+k<int(s.size())&&p[k]==s[i+k])k++;CHECK(b[i+1]==k);}}
}
}

namespace T108 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/rolling_hash.hpp"
void test(){
string a;for(int i=0;i<256;i++)a+=char(i);RollingHash s(a,1000003);for(int l=1;l<=256;l++)for(int r=l;r<=256;r++){u64 x=0;for(int i=l;i<=r;i++)x=x*s.base+(unsigned char)a[i-1]+1;CHECK(s.get(l,r)==x);}
}
}

namespace T109 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/subsequence_automaton.hpp"
void test(){
for(int z=0;z<200;z++){string a(rnd(0,30),'0');for(char&c:a)c+=rnd(0,3);SeqAM s(a,4,'0');for(int k=0;k<100;k++){string b(rnd(0,10),'0');for(char&c:b)c+=rnd(0,3);int i=0;for(char c:a)if(i<int(b.size())&&b[i]==c)i++;CHECK(s.check(b)==(i==int(b.size())));}CHECK(!s.check("a"));}
}
}

namespace T110 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/trie.hpp"
void test(){
Trie<>s;multiset<string>a;for(int z=0;z<500;z++){string v(rnd(0,5),'a');for(char&c:v)c+=rnd(0,2);if(rnd(0,1))s.insert(v),a.insert(v);else{auto it=a.find(v);CHECK(s.erase(v)==(it!=a.end()));if(it!=a.end())a.erase(it);}CHECK(s.count(v)==int(a.count(v)));int k=0;for(auto x:a)k+=x.substr(0,v.size())==v;CHECK(s.countPrefix(v)==k);}
}
}

namespace T111 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/aho_corasick.hpp"
void test(){
for(int z=0;z<100;z++){AC s;vector<string>a;vector<int>ids;for(int i=0;i<20;i++){string p(rnd(1,6),'a');for(char&c:p)c+=rnd(0,2);a.push_back(p);ids.push_back(s.add(p));}s.build();string t(50,'a');for(char&c:t)c+=rnd(0,2);auto v=s.match(t);CHECK(s.match(t)==v);for(int i=0;i<20;i++){int k=0;for(int j=0;j+int(a[i].size())<=int(t.size());j++)k+=t.substr(j,a[i].size())==a[i];CHECK(v[ids[i]]==k);}}
}
}

namespace T112 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/sam.hpp"
void test(){
for(int z=0;z<200;z++){string a(rnd(0,25),'a');for(char&c:a)c+=rnd(0,2);SAM s; for(char c:a)s.add(c);map<string,int>cnt;for(int i=0;i<int(a.size());i++)for(int j=i+1;j<=int(a.size());j++)cnt[a.substr(i,j-i)]++;CHECK(s.distinct()==i64(cnt.size()));s.count();s.count();for(auto [v,k]:cnt)CHECK(s.occ(v)==k);CHECK(s.occ("")==int(a.size())+1);string b(20,'a');for(char&c:b)c+=rnd(0,3);int best=0;for(int i=0;i<int(b.size());i++)for(int j=i+1;j<=int(b.size());j++)if(cnt.count(b.substr(i,j-i)))best=max(best,j-i);CHECK(s.lcs(b)==best);}
}
}

namespace T113 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/suffix_array.hpp"
void test(){
for(int z=0;z<200;z++){string a(rnd(0,40),'a');for(char&c:a)c+=rnd(0,3);SA s(a);vector<int>p(a.size());iota(p.begin(),p.end(),1);sort(p.begin(),p.end(),[&](int x,int y){return a.substr(x-1)<a.substr(y-1);});for(int i=1;i<=int(a.size());i++){CHECK(s.sa[i]==p[i-1]);if(i>1){int k=0,x=p[i-1]-1,y=p[i-2]-1;while(x+k<int(a.size())&&y+k<int(a.size())&&a[x+k]==a[y+k])k++;CHECK(s.height[i]==k);}}}
}
}

namespace T114 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/minimal_rotation.hpp"
void test(){
for(int z=0;z<300;z++){string a(rnd(0,30),'a');for(char&c:a)c+=rnd(0,3);if(a.empty()){CHECK(minRotation(a)==0);continue;}string b=a;for(int i=1;i<int(a.size());i++)b=min(b,a.substr(i)+a.substr(0,i));int k=minRotation(a);CHECK(a.substr(k)+a.substr(0,k)==b);}
}
}

namespace T115 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/manacher.hpp"
void test(){
for(int z=0;z<300;z++){string a(rnd(0,30),'a');for(char&c:a)c=string("a$#&")[rnd(0,3)];int ans=0;for(int i=0;i<int(a.size());i++)for(int j=i;j<int(a.size());j++){bool p=true;for(int l=i,r=j;l<r;l++,r--)p&=a[l]==a[r];if(p)ans=max(ans,j-i+1);}CHECK(longestPal(a)==ans);}
}
}

namespace T116 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/eertree.hpp"
void test(){
for(int z=0;z<200;z++){string a(rnd(0,30),'a');for(char&c:a)c+=rnd(0,2);map<string,int>b;for(int i=0;i<int(a.size());i++)for(int j=i+1;j<=int(a.size());j++){string v=a.substr(i,j-i),r=v;reverse(r.begin(),r.end());if(v==r)b[v]++;}PAM s(a);CHECK(s.distinct()==int(b.size()));s.count();vector<int>x,y;for(auto [v,k]:b)x.push_back(k);for(int i=2;i<s.size();i++)y.push_back(s.tr[i].cnt);sort(x.begin(),x.end());sort(y.begin(),y.end());CHECK(x==y);s.count();vector<int>t;for(int i=2;i<s.size();i++)t.push_back(s.tr[i].cnt);sort(t.begin(),t.end());CHECK(t==y);}
}
}

namespace T117 {
#include "D:/Programme/GitCode/Algorithm/算法竞赛模板/code/point.hpp"
void test(){
Point<i64>a(10000000000LL,10000000000LL),b(-10000000000LL,10000000000LL);CHECK(cross(a,b)==__int128(2000000000000000000LL)*100);CHECK(dot(a,a)==__int128(2000000000000000000LL)*100);
}
}
int main(){
T100::test(); cout<<"PASS ntt "<<checks<<"\n";
T101::test(); cout<<"PASS fwt "<<checks<<"\n";
T102::test(); cout<<"PASS fps "<<checks<<"\n";
T103::test(); cout<<"PASS gauss "<<checks<<"\n";
T104::test(); cout<<"PASS xor_basis "<<checks<<"\n";
T105::test(); cout<<"PASS xor_system "<<checks<<"\n";
T106::test(); cout<<"PASS kmp "<<checks<<"\n";
T107::test(); cout<<"PASS z_function "<<checks<<"\n";
T108::test(); cout<<"PASS rolling_hash "<<checks<<"\n";
T109::test(); cout<<"PASS subsequence_automaton "<<checks<<"\n";
T110::test(); cout<<"PASS trie "<<checks<<"\n";
T111::test(); cout<<"PASS aho_corasick "<<checks<<"\n";
T112::test(); cout<<"PASS sam "<<checks<<"\n";
T113::test(); cout<<"PASS suffix_array "<<checks<<"\n";
T114::test(); cout<<"PASS minimal_rotation "<<checks<<"\n";
T115::test(); cout<<"PASS manacher "<<checks<<"\n";
T116::test(); cout<<"PASS eertree "<<checks<<"\n";
T117::test(); cout<<"PASS point "<<checks<<"\n";
}
