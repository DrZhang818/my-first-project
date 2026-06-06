#include<bits/stdc++.h>
using namespace std;
int a[500001],m,n,t;
bool v[500001];
int main(){
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    for(cin>>t;t;t--){
        cin>>n;
        m=0;
        for(int i=1;i<=n;i++){
            v[i]=0;
        }
        for(int i=1;i<=n;i++){
            cin>>a[i];
            m+=a[i]==n||!v[a[i]+1];
            v[a[i]]=1;
        }
        cout<<m<<'\n';
    }
    return 0;
}