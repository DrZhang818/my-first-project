#include<bits/stdc++.h>
using namespace std;
int m,n,t;
double dp[3001];
tuple<int,int,int>a[3001];
int main(){
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    for(cin>>t;t;t--){
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            cin>>get<1>(a[i])>>get<0>(a[i])>>get<2>(a[i]);
        }
        sort(a+1,a+n+1);
        for(int j=m;j>=0;j--){
            dp[j]=0;
        }
        for(int i=1;i<=n;i++){
            for(int j=m;j>=get<2>(a[i]);j--){
                dp[j]=max(dp[j],1.0*get<1>(a[i])*get<0>(a[i])/100+1.0*(100-get<1>(a[i]))*dp[j-get<2>(a[i])]/100);
            }
        }
        cout<<fixed<<setprecision(10)<<dp[m]<<'\n';
    }
    return 0;
}