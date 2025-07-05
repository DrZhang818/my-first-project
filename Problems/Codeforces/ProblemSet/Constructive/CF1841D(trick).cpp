#include<bits/stdc++.h>
using namespace std;
int n,p,r,t;
struct str{
    int l,r;
    friend bool operator<(str i,str j){
        return i.r<j.l;
    }
}a[2001];
bool check(int l,int r){
    int q=0;
    set<str>s;
    for(int i=1;i<=n;i++){
        if(l<=a[i].l&&a[i].r<=r){
            s.insert(a[i]);
            q++;
        }
    }
    return s.size()<q;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    for(cin>>t;t;t--){
        cin>>n;
        p=0;
        r=0;
        for(int i=1;i<=n;i++){
            cin>>a[i].l>>a[i].r;
        }
        while(check(p,1000000000)){
            int lf = p - 1,rt=1000000000,mid;
            while(lf + 1 < rt){
                mid = lf + rt >> 1;
                if(check(p,mid)){
                    rt = mid;
                }else{
                    lf = mid;
                }
            }
            r+=2;
            p=rt + 1;
        }
        cout<<n-r<<'\n';
    }
    return 0;
}