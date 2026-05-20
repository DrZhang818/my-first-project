#include<bits/stdc++.h>
using namespace std;
int n;
pair<int,int>a[200001];
int main(){
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].first>>a[i].second;
    }
    sort(a+1,a+n+1);
    cout<<"YES\n";
    for(int i=1;i<=n-1;i++){
        cout<<a[i].first<<' '<<a[i].second<<'\n';
    }
    return 0;
}