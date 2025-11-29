#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
ll re(){
	ll s=0,w=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')w=-w;c=getchar();}
	while(isdigit(c)){s=(s<<1)+(s<<3)+(c^48);c=getchar();}
	return s*w;
}
const int D=1e5+114;
char sb[D];
int s[D],t[D],ans[D];
int ones[D],onet[D];
int pre1[D],pre2[D];
int q,n,m;
void pre(){
	scanf("%s",sb+1);
	n=strlen(sb+1);
	for(int i=1;i<=n;i++){
		if(sb[i]=='A')s[i]=0;
		else s[i]=1;
		ones[i]=(ones[i-1]+s[i]);
//		cout<<ones[i]<<" ";
	}
	for(int i=1;i<=n;i++){
		if(s[i]==1)pre1[i]=i;
		else pre1[i]=pre1[i-1];
	//	cout<<pre1[i]<<" ";
	}
//	puts("");
	scanf("%s",sb+1);
	m=strlen(sb+1);
	for(int i=1;i<=m;i++){
		if(sb[i]=='A')t[i]=0;
		else t[i]=1;
		onet[i]=(onet[i-1]+t[i]);
	}
	for(int i=1;i<=m;i++){
		if(t[i]==1)pre2[i]=i;
		else pre2[i]=pre2[i-1];
	}
	q=re();
}
void debug(){
	for(int i=1;i<=n;i++){
		cout<<"SB: "<<ones[i]<<" "<<pre1[i]<<endl;
	}
	for(int i=1;i<=m;i++){
		cout<<"NT: "<<onet[i]<<" "<<pre2[i]<<endl;
	}
}
int main()
{
	freopen("always.in","r",stdin);
	freopen("always.out","w",stdout);
	pre();
//	debug();
//	puts("");
	for(int cnt=1;cnt<=q;cnt++){
		int a,b,c,d;
		a=re();b=re();c=re();d=re();
		int dog=onet[d]-onet[c-1];
		int cat=ones[b]-ones[a-1];
		int num=dog-cat;
		if((num&1)||num<0){
//			cout<<"y"<<endl;
			ans[cnt]=0;continue;}//num1 can`t be equal
		int zeros,zerot;
		if(pre1[b]<a){zeros=b-a+1;}
		else zeros=b-pre1[b];
		if(pre2[d]<c){zerot=d-c+1;}
		else zerot=d-pre2[d];
//		cout<<endl<<pre2[d];
//		cout<<endl<<zerot<<" "<<zeros<<" "<<cat<<" "<<dog<<" "<<num<<endl;
		if(zeros<zerot){
//			cout<<"x"<<endl;
			ans[cnt]=0;continue;}
		
		if(zerot==d-c+1){
			if(cat>0){
//			cout<<"t"<<endl;
			ans[cnt]=0;continue;}
		}
		if(num==0){
			if((zeros-zerot)%3!=0){
//				cout<<"q"<<endl;
				ans[cnt]=0;continue;
			}
		}//two string num1 equal but final num0 does`n equal
		
		if(cat==0&&dog!=0&&zeros==zerot){
			ans[cnt]=0;continue;
		}
		
		ans[cnt]=1;
	}
	for(int i=1;i<=q;i++){
		printf("%d",ans[i]);
	}
	return 0;
}//sb dev can