#include<bits/stdc++.h>
using namespace std;
int k,n,t;
bool b[1000001];
vector<pair<bool,int>>s;
string o;
int main(){
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>o;
    if(o=="Alice"){
        for(cin>>t;t;t--){
            cin>>n>>k;
            for(int i=1;i<=n;i++){
                b[i]=0;
            }
            for(int i,j=1;j<=k;j++){
                cin>>i;
                b[i]=1;
            }
            s.clear();
            for(int i=1;i<=n;i++){
                if(b[i]&&!s.empty()&&!s.back().first){
                    s.pop_back();
                }else{
                    s.push_back(make_pair(b[i],i));
                }
            }
            for(int j=0;j<s.size();j++){
                if(!s[j].first){
                    b[s[j].second]=1;
                    break;
                }
            }
            for(int i=1;i<=n;i++){
                if(b[i]){
                    cout<<i<<' ';
                }
            }
            cout<<'\n';
        }
    }else if(o=="Bob"){
        for(cin>>t;t;t--){
            cin>>n>>k;
            for(int i=1;i<=n;i++){
                b[i]=0;
            }
            for(int i,j=1;j<=k+1;j++){
                cin>>i;
                b[i]=1;
            }
            s.clear();
            for(int i=1;i<=n;i++){
                if(b[i]&&!s.empty()&&!s.back().first){
                    s.pop_back();
                }else{
                    s.push_back(make_pair(b[i],i));
                }
            }
            for(int j=(int)s.size()-1;j>=0;j--){
                if(s[j].first){
                    cout<<s[j].second<<'\n';
                    break;
                }
            }
        }
    }
    return 0;
}