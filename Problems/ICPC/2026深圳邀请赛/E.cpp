#include<bits/stdc++.h>
using namespace std;
int a[2][2],b[2][2],c[2],d[2],m[2],n,p,t;
bool f[2];
string s[2];
priority_queue<int,vector<int>,greater<int>>q[2];
int main(){
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    for(cin>>t;t;t--){
        cin>>n>>s[0]>>s[1]>>p;
        b[0][0]=0;
        b[1][0]=0;
        b[0][1]=0;
        b[1][1]=0;
        for(int i=1;i<=n;i++){
            b[0][i>=p]+=s[0][i-1]=='1';
            b[1][i>=p]+=s[1][i-1]=='1';
        }
        c[0]=0;
        while(!q[0].empty()){
            q[0].pop();
        }
        while(!q[1].empty()){
            q[1].pop();
        }
        for(int i=p;i<=n;i++){
            if(s[0][i-1]=='1'){
                q[0].push(i);
            }
            if(s[1][i-1]=='1'){
                q[1].push(i);
            }
        }
        while(!q[0].empty()&&!q[1].empty()){
            while(!q[0].empty()&&q[0].top()<=q[1].top()){
                q[0].pop();
            }
            if(!q[0].empty()){
                c[0]++;
                q[0].pop();
            }
            q[1].pop();
        }
        c[1]=0;
        while(!q[0].empty()){
            q[0].pop();
        }
        while(!q[1].empty()){
            q[1].pop();
        }
        for(int i=1;i<=n;i++){
            if(s[0][i-1]=='2'){
                q[0].push(i);
            }
            if(s[1][i-1]=='2'){
                q[1].push(i);
            }
        }
        while(!q[0].empty()&&!q[1].empty()){
            while(!q[0].empty()&&q[0].top()<=q[1].top()){
                q[0].pop();
            }
            if(!q[0].empty()){
                c[1]++;
                q[0].pop();
            }
            q[1].pop();
        }
        f[0]=b[1][1]>=b[0][0]-1&&c[0]+c[1]>=b[0][0]-1;
        a[0][0]=0;
        for(int i=1;i<=n;i++){
            if(s[0][i-1]=='1'){
                a[0][0]=i;
                break;
            }
        }
        a[1][0]=0;
        for(int i=n;i>=p;i--){
            if(s[1][i-1]=='1'){
                a[1][0]=i;
                break;
            }
        }
        a[0][1]=0;
        for(int i=1;i<=n;i++){
            if(s[0][i-1]=='2'){
                a[0][1]=i;
                break;
            }
        }
        a[1][1]=0;
        for(int i=n;i>=1;i--){
            if(s[1][i-1]=='2'){
                a[1][1]=i;
                break;
            }
        }
        d[0]=0;
        for(int i=1;i<=n;i++){
            if(s[0][i-1]=='1'){
                d[0]=i;
                break;
            }
        }
        d[1]=0;
        for(int i=n;i>=1;i--){
            if(s[1][i-1]=='1'){
                d[1]=i;
                break;
            }
        }
        m[0]=0;
        m[1]=0;
        for(int i=1;i<=n;i++){
            m[0]+=s[0][i-1]-'0';
            m[1]+=s[1][i-1]-'0';
        }
        f[1]=b[1][0]<=1&&(a[0][0]!=0&&a[1][0]!=0&&a[0][0]<a[1][0]||a[0][1]!=0&&a[1][1]!=0&&a[0][1]<a[1][1])||d[0]!=0&&d[1]!=0&&d[0]<d[1]&&m[1]==1;
        cout<<(f[0]||f[1]?"Yes\n":"No\n");
    }
    return 0;
}