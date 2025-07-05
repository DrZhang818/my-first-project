#include <bits/stdc++.h>
using namespace std;

long long h,w,d,q,l,r,ans,scan;
long long dist[90000],pres[90000];
unordered_map<long long,pair<long long,long long>>dian;



int main(){
	scanf("%lld %lld %lld",&h,&w,&d);
	for(long long i = 0;i<h;i++){
		for(long long j = 0;j<w;j++){
			scanf("%lld",&scan);
			dian[scan] = {i,j};
		}
	}
	
	//计算距离
	for(long long i = h * w - d; i >= 1; i--){
		dist[i] = abs(dian[i+d].first-dian[i].first) + abs(dian[i+d].second-dian[i].second);
		pres[i] = dist[i] + pres[i + d];
	}
	
	//输出答案
	scanf("%lld",&q);
	for(long long i = 0;i<q;i++){
		scanf("%lld %lld",&l,&r);
		ans = pres[l] - pres[r]; 
		printf("%lld\n",ans);
	}
	return 0;
}