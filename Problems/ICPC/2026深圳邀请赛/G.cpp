#include<bits/stdc++.h>
using namespace std;
int k,l,m,n,t;
bool f;
pair<int,int>p,q;
vector<pair<int,int>>g[2];
string s;
void check(vector<pair<int,int>>&a){
    for(int i=0;i<a.size();i++){
        assert(abs(a[(i+1)%a.size()].first-a[i].first)+abs(a[(i+1)%a.size()].second-a[i].second)==1);
    }
}
void move(pair<int,int>&p,pair<int,int>&q){
    if(p.first-1==q.first&&p.second==q.second){
        s+='U';
    }else if(p.first+1==q.first&&p.second==q.second){
        s+='D';
    }else if(p.first==q.first&&p.second-1==q.second){
        s+='L';
    }else if(p.first==q.first&&p.second+1==q.second){
        s+='R';
    }else{
        assert(0);
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    for(cin>>t;t;t--){
        cin>>n>>m>>p.first>>p.second;
        if(n*m%2==0){
            l=n*m;
            if(n%2==0){
                for(int i=1;i<=n;i+=2){
                    for(int j=2;j<=m;j++){
                        g[0].push_back(make_pair(i,j));
                        g[1].push_back(make_pair(i,j));
                    }
                    for(int j=m;j>=2;j--){
                        g[0].push_back(make_pair(i+1,j));
                        g[1].push_back(make_pair(i+1,j));
                    }
                }
                for(int i=n;i>=1;i--){
                    g[0].push_back(make_pair(i,1));
                    g[1].push_back(make_pair(i,1));
                }
            }else if(m%2==0){
                for(int j=1;j<=m;j+=2){
                    for(int i=2;i<=n;i++){
                        g[0].push_back(make_pair(i,j));
                        g[1].push_back(make_pair(i,j));
                    }
                    for(int i=n;i>=2;i--){
                        g[0].push_back(make_pair(i,j+1));
                        g[1].push_back(make_pair(i,j+1));
                    }
                }
                for(int j=m;j>=1;j--){
                    g[0].push_back(make_pair(1,j));
                    g[1].push_back(make_pair(1,j));
                }
            }
        }else{
            l=n*m-1;
            g[0].push_back(make_pair(1,1));
            g[1].push_back(make_pair(2,2));
            for(int i=2;i<=n;i++){
                g[0].push_back(make_pair(i,1));
                g[1].push_back(make_pair(i,1));
            }
            for(int i=n;i>=4;i-=2){
                for(int j=2;j<=m;j++){
                    g[0].push_back(make_pair(i,j));
                    g[1].push_back(make_pair(i,j));
                }
                for(int j=m;j>=2;j--){
                    g[0].push_back(make_pair(i-1,j));
                    g[1].push_back(make_pair(i-1,j));
                }
            }
            for(int j=2;j<=m;j++){
                g[0].push_back(make_pair(3,j));
                g[1].push_back(make_pair(3,j));
            }
            for(int j=m;j>=4;j-=2){
                g[0].push_back(make_pair(2,j));
                g[1].push_back(make_pair(2,j));
                g[0].push_back(make_pair(1,j));
                g[1].push_back(make_pair(1,j));
                g[0].push_back(make_pair(1,j-1));
                g[1].push_back(make_pair(1,j-1));
                g[0].push_back(make_pair(2,j-1));
                g[1].push_back(make_pair(2,j-1));
            }
            g[0].push_back(make_pair(2,3));
            g[1].push_back(make_pair(2,3));
            g[0].push_back(make_pair(1,3));
            g[1].push_back(make_pair(1,3));
            g[0].push_back(make_pair(1,2));
            g[1].push_back(make_pair(1,2));
        }
        assert(g[0].size()==l);
        assert(g[1].size()==l);
        check(g[0]);
        check(g[1]);
        k=-1;
        for(int i=0;i<l;i++){
            if(p==g[0][i]){
                f=0;
                k=i;
            }else if(p==g[1][i]){
                f=1;
                k=i;
            }
        }
        assert(k!=-1);
        for(int h=1;h<=n*m-1;h++){
            cin>>q.first>>q.second;
            s="";
            if(q==make_pair(1,1)){
                f=0;
            }else if(q==make_pair(2,2)){
                f=1;
            }
            while(p!=q){
                k=(k+1)%l;
                move(p,g[f][k]);
                p=g[f][k];
            }
            cout<<s<<endl;
        }
        g[0].clear();
        g[1].clear();
    }
    return 0;
}