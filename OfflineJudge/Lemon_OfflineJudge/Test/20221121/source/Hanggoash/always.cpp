#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
template<typename T>inline void re(T &x)
{
	x=0;
	int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
	x*=f;	
}
template<typename T>inline void wr(T x)
{
	if(x<0)putchar('-'),x=-x;
	if(x>9)wr(x/10);
	putchar(x%10^48);
}
const int maxn=1e5+10;
char s[maxn],t[maxn];
int lens,lent;
int c1s[maxn],c1t[maxn];
int pres[maxn],pret[maxn];
inline void prework()
{
	scanf("%s %s",s+1,t+1);
	lens=strlen(s+1),lent=strlen(t+1);
	for(int i=1;i<=lens;++i)c1s[i]=c1s[i-1]+(s[i]=='B'||s[i]=='C');
	for(int i=1;i<=lent;++i)c1t[i]=c1t[i-1]+(t[i]=='B'||t[i]=='C');
	int nowpos=(s[1]=='A'?1:-1);
	for(int i=1;i<=lens;++i)
	{
		if(nowpos==-1)
		{
			if(s[i]=='A')nowpos=i,pres[i]=i;
			else pres[i]=-1;
		}
		else
		{
			if(s[i]=='A')pres[i]=nowpos;
			else nowpos=-1,pres[i]=-1;
		}
	}
	nowpos=(t[1]=='A'?1:-1);
	for(int i=1;i<=lent;++i)
	{
		if(nowpos==-1)
		{
			if(t[i]=='A')nowpos=i,pret[i]=i;
			else pret[i]=-1;
		}
		else
		{
			if(t[i]=='A')pret[i]=nowpos;
			else nowpos=-1,pret[i]=-1;
		}
	}
}
inline void input(int &l1,int &r1,int &l2,int &r2){re(l1),re(r1),re(l2),re(r2);}
inline void debug()
{
	for(int i=1;i<=lens;++i)printf("%d ",c1s[i]);putchar('\n');
	for(int i=1;i<=lent;++i)printf("%d ",c1t[i]);putchar('\n');
	for(int i=1;i<=lens;++i)printf("%d ",pres[i]);putchar('\n');
	for(int i=1;i<=lent;++i)printf("%d ",pret[i]);putchar('\n');
}
inline bool check_minus(int l1,int r1,int l2,int r2)
{
	int vs=c1s[r1]-c1s[l1-1],vt=c1t[r2]-c1t[l2-1];
	return vt>=vs&&((vt-vs)%2==0);
}
char ans[maxn];
int num=0;
int main()
{
	freopen("always.in","r",stdin);
	freopen("always.out","w",stdout);
	prework();
//	debug();
	int q,l1,r1,l2,r2;
	re(q);
	for(num=1;num<=q;++num)
	{
//		printf("%d:\n",num);
		input(l1,r1,l2,r2);
		if(s[r1]=='B'||s[r1]=='C')//1
		{
			if(t[r2]=='A')ans[num]='0';//0
			else ans[num]=check_minus(l1,r1,l2,r2)?'1':'0';//1
		}
		else//0
		{
			if(t[r2]=='A')//0
			{
				int pS=max(pres[r1],l1),pT=max(pret[r2],l2);
				if(pT==l2)
				{
					if(r1-pS+1<r2-pT+1||pS!=l1)ans[num]='0';
					else ans[num]=((r1-pS+1)%3==(r2-pT+1)%3)?'1':'0';
				}
				else
				{
					if(r1-pS+1<r2-pT+1)ans[num]='0';
					else 
					{
//						if((r1-pS+1)%3==(r2-pT+1)%3)
//							if(pres[r1]>=l1&&pret[r2]>=l2&&check_minus(l1,pres[r1]-1,l2,pret[r2]-1)){ans[num]='1';continue;}
						int len=r2-pT+1;
						r1-=len,r2-=len;
						if(r1<l1)ans[num]=r1<l1?'0':'1';
//						printf("%d %d\n%d %d\n",l1,r1,l2,r2);
						else if(s[r1]=='A'&&(t[r2]=='B'||t[r2]=='C')&&c1s[r1]-c1s[l1-1]>=c1t[r2]-c1t[l2-1]){ans[num]='0';continue;}
						else ans[num]=(check_minus(l1,r1,l2,r2))?'1':'0';/////
					}
				}
			}
			else
			{
				int pS=max(pres[r1],l1);
				if((r1-pS+1)%3==0)
					ans[num]=check_minus(l1,pres[r1]-1,l2,r2)?'1':'0';
				else if(c1s[r1]-c1s[l1-1]>=c1t[r2]-c1t[l2-1]){ans[num]='0';continue;}
			 	else ans[num]=check_minus(l1,r1,l2,r2)?'1':'0';//1
			 	
			}
		}
	}
	for(int i=1;i<=num;++i)printf("%c",ans[i]);
	return 0;
}