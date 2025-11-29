#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
template <typename T>inline void re(T &x){
	x=0;
	char c=getchar();
	T neg=0;
	while(!isdigit(c))neg|=!(c^'-'),c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	if(neg)x=(~x)+1;
}
const int N=1e5+10;
char s[N],t[N];
int sum1b[N],sum2b[N];
int T,lens,lent;
int a1[N],a2[N],cnt1,cnt2;
bool work(){
	int sl,sr,tl,tr;
	re(sl),re(sr),re(tl),re(tr);
	int numb1=sum1b[sr]-sum1b[sl-1];
	int numb2=sum2b[tr]-sum2b[tl-1];
	if(numb1%2!=numb2%2)return 0;
	if(numb1>numb2)return 0;
	int taila1=0,taila2=0;
	for(int i=sr;i>=sl;i--){
		if(s[i]!='B')taila1++;
		else break;
	}
	for(int i=tr;i>=tl;i--){
		if(t[i]!='B')taila2++;
		else break;
	}	
	if(taila2>taila1)return 0;
	if(numb1==0&&numb2!=0&&(taila1==0||taila1-taila2==0))return 0;
	int lasta=(taila1-taila2)%3;
	if(lasta!=0)numb1+=2;
	if(numb1>numb2)return 0;
	return 1;
}
int main(){
	freopen("always.in","r",stdin);
	freopen("ans.out","w",stdout);
	scanf("%s%s",s+1,t+1);
	re(T);
	lens=strlen(s+1);
	lent=strlen(t+1);
	for(int i=1;i<=lens;i++){
		if(s[i]=='C')s[i]='B';
		if(s[i]=='B')sum1b[i]++;
		sum1b[i]+=sum1b[i-1];
	}
	for(int i=1;i<=lent;i++){
		if(t[i]=='C')t[i]='B';
		if(t[i]=='B')sum2b[i]++;
		sum2b[i]+=sum2b[i-1];
	}	
	while(T--){
		if(work())putchar('1');
		else putchar('0');
	}
	return 0;
}