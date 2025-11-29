#include<bits/stdc++.h>
using namespace std;
int random(int x){return 1ll*rand()*rand()%x+1;}

int main()
{
	freopen("always.in","w",stdout);
	srand(time(0));
	int len1=random(20),len2=random(20);
	for(int i=1;i<=len1;++i)putchar(random(3)-1+'A');putchar('\n');
	for(int i=1;i<=len2;++i)putchar(random(3)-1+'A');putchar('\n');
	int q=random(15);
	printf("%d\n",q);
	while(q--)
	{
		int l1,r1,l2,r2;
		while(l1=random(len1),r1=random(len1))
			if(l1<=r1)break;	
		while(l2=random(len2),r2=random(len2))
			if(l2<=r2)break;	
		printf("%d %d %d %d\n",l1,r1,l2,r2);
	}
	return 0;
}