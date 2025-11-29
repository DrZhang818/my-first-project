#include<bits/stdc++.h>
#define R register 
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
int T,n,m;
int main()
{
	freopen("potato.in","r",stdin);
	freopen("potato.out","w",stdout);
	re(T);
	while(T--)
	{
		int n,m;
		re(n),re(m);
		int a[n+4][m+4],b[n+4][m+4];
		for(R int i=1;i<=n;++i)
			for(R int j=1;j<=m;++j)
				re(a[i][j]),b[i][j]=a[i][j];
		int lrec1=0,lrec2=0;
		for(R int i=1;i<=n;++i)
		{
			sort(a[i]+1,a[i]+m+1);
			int tmp=0;
			int trec1=0,trec2=0;
			for(R int j=1;j<=m;++j)
			{
				if(a[i][j]==b[i][j])continue;
				tmp++;
				if(!trec1)trec1=j;
				else trec2=j;
			}
			if(tmp>2)goto Invalid;
			if(!trec1&&!trec2)continue;
			if(!lrec1&&!lrec2){lrec1=trec1,lrec2=trec2;continue;}
			else if(trec1!=lrec1||trec2!=lrec2)goto Invalid;
		}
		Valid:
			{
				lrec1+=(!lrec1),lrec2+=(!lrec2);
				for(R int i=1;i<=n;++i)
				{
					swap(b[i][lrec1],b[i][lrec2]);
					for(R int j=2;j<=m;++j)
						if(b[i][j]<b[i][j-1])goto Invalid;
				}
				wr(lrec1),putchar(' '),wr(lrec2),putchar('\n');
				continue;
			}
		Invalid:
				puts("-1");

	}
	return 0;
}