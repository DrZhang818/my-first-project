#include<bits/stdc++.h>
using namespace std;
char s[5010];int dp[5010][5010];
int main(){
    scanf("%s",s);int n=strlen(s),ans=0;
    for(int i=0;i<n;i++) dp[i][i]=0;
    for(int i=0;i<n-1;i++) dp[i][i+1]=(s[i]>s[i+1]);//初始值
    for(int len=3;len<=n;len++){
        for(int i=0;i<n-len+1;i++){
            int j=i+len-1;
            if(s[i]==s[j]) dp[i][j]=dp[i+1][j-1];
            else if(s[i]>s[j]) dp[i][j]=1;
        }
    }
    for(int i=0;i<n;i++)
        for(int j=i;j<n;j++) ans+=dp[i][j];//求总数
    printf("%d",ans);
    return 0;
}