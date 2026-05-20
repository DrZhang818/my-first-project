#include<bits/stdc++.h>
using namespace std;
int m,n,t;
long long a[500001],r;
pair<long long,long long>b[500001];
multiset<long long>s;
bool cmp(pair<long long,long long>i,pair<long long,long long>j){
    return i.second>j.second;
}
long long cal(){
    long long w=0;
    for(int i=1;i<=n;i++){
        s.insert(a[i]);
    }
    for(int j=1;j<=m;j++){
        set<long long>::iterator it=s.lower_bound(b[j].second);
        if(it==s.end()){
            it--;
        }
        long long k=min(b[j].second,*it);
        if(b[j].first<k){
            w+=*it-k;
            s.erase(it);
            s.insert(b[j].first);
        }
    }
    while(!s.empty()){
        w+=*s.begin();
        s.erase(s.begin());
    }
    return w;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    for(cin>>t;t;t--){
        cin>>n>>m;
        r=0;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            r+=a[i];
        }
        for(int j=1;j<=m;j++){
            cin>>b[j].first;
        }
        for(int j=1;j<=m;j++){
            cin>>b[j].second;
        }
        sort(b+1,b+m+1,cmp);
        r=min(cal(),r);
        cout<<r<<'\n';
    }
    return 0;
}