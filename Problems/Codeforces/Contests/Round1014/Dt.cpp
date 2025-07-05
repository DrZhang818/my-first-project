#include<bits/stdc++.h>
using namespace std;
int b[3],n,p,t;
bool f;
string s;
queue<int>q;
bool check(int x,char c){
    return s[x]!=s[x+1]&&s[x]!=c&&s[x+1]!=c;
}
void insert(int x){
    q.push(x+1);
    if(check(x,'L')){
        b[0]++;
        s=s.substr(0,x+1)+'L'+s.substr(x+1,(int)s.size()-x-1);
    }else if(check(x,'I')){
        b[1]++;
        s=s.substr(0,x+1)+'I'+s.substr(x+1,(int)s.size()-x-1);
    }else if(check(x,'T')){
        b[2]++;
        s=s.substr(0,x+1)+'T'+s.substr(x+1,(int)s.size()-x-1);
    }else{
        assert(0);
    }
    //assert(q.size()<=2*n);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    for(cin>>t;t;t--){
        cin>>n>>s;
        memset(b,0,sizeof(b));
        for(int i=0;i<s.size();i++){
            if(s[i]=='L'){
                b[0]++;
            }else if(s[i]=='I'){
                b[1]++;
            }else if(s[i]=='T'){
                b[2]++;
            }
        }
        if(b[0]==0&&b[1]==0||b[0]==0&&b[2]==0||b[1]==0&&b[2]==0){
            cout<<-1<<'\n';
        }else{
            if(b[0]>b[1]&&b[0]>b[2]){
                while(b[0]>b[1]&&b[0]>b[2]){
                    for(int i=0;i<(int)s.size()-1;i++){
                        if(check(i,'I')||check(i,'T')){
                            insert(i);
                            break;
                        }
                    }
                }
            }else if(b[1]>b[0]&&b[1]>b[2]){
                while(b[1]>b[0]&&b[1]>b[2]){
                    for(int i=0;i<(int)s.size()-1;i++){
                        if(check(i,'L')||check(i,'T')){
                            insert(i);
                            break;
                        }
                    }
                }
            }else if(b[2]>b[0]&&b[2]>b[1]){
                while(b[2]>b[0]&&b[2]>b[1]){
                    for(int i=0;i<(int)s.size()-1;i++){
                        if(check(i,'L')||check(i,'I')){
                            insert(i);
                            break;
                        }
                    }
                }
            }
            if(b[0]<b[1]&&b[0]<b[2]){
                do{
                    f=0;
                    for(int i=0;i<(int)s.size()-1;i++){
                        if(check(i,'L')){
                            f=1;
                            insert(i);
                            break;
                        }
                    }
                }while(b[0]<b[1]&&b[0]<b[2]&&f);
                while(b[0]<b[1]&&b[0]<b[2]){
                    p=-1;
                    for(int i=0;i<(int)s.size()-1;i++){
                        if(check(i,'I')){
                            p=i;
                            break;
                        }
                    }
                    if(p==-1){
                        for(int i=0;i<(int)s.size();i++){
                            if(check(i,'T')){
                                insert(i);
                                break;
                            }
                        }
                        for(int i=0;i<(int)s.size()-1;i++){
                            if(check(i,'L')){
                                insert(i);
                                break;
                            }
                        }
                        for(int i=0;i<(int)s.size();i++){
                            if(check(i,'I')){
                                insert(i);
                                break;
                            }
                        }
                        for(int i=0;i<(int)s.size()-1;i++){
                            if(check(i,'L')){
                                insert(i);
                                break;
                            }
                        }
                    }else{
                        for(int i=0;i<(int)s.size();i++){
                            if(check(i,'I')){
                                insert(i);
                                break;
                            }
                        }
                        for(int i=0;i<(int)s.size()-1;i++){
                            if(check(i,'L')){
                                insert(i);
                                break;
                            }
                        }
                        for(int i=0;i<(int)s.size();i++){
                            if(check(i,'T')){
                                insert(i);
                                break;
                            }
                        }
                        for(int i=0;i<(int)s.size()-1;i++){
                            if(check(i,'L')){
                                insert(i);
                                break;
                            }
                        }
                    }
                }
            }else if(b[1]<b[0]&&b[1]<b[2]){
                do{
                    f=0;
                    for(int i=0;i<(int)s.size()-1;i++){
                        if(check(i,'I')){
                            f=1;
                            insert(i);
                            break;
                        }
                    }
                }while(b[1]<b[0]&&b[1]<b[2]&&f);
                while(b[1]<b[0]&&b[1]<b[2]){
                    p=-1;
                    for(int i=0;i<(int)s.size()-1;i++){
                        if(check(i,'L')){
                            p=i;
                            break;
                        }
                    }
                    if(p==-1){
                        for(int i=0;i<(int)s.size();i++){
                            if(check(i,'T')){
                                insert(i);
                                break;
                            }
                        }
                        for(int i=0;i<(int)s.size()-1;i++){
                            if(check(i,'I')){
                                insert(i);
                                break;
                            }
                        }
                        for(int i=0;i<(int)s.size();i++){
                            if(check(i,'L')){
                                insert(i);
                                break;
                            }
                        }
                        for(int i=0;i<(int)s.size()-1;i++){
                            if(check(i,'I')){
                                insert(i);
                                break;
                            }
                        }
                    }else{
                        for(int i=0;i<(int)s.size();i++){
                            if(check(i,'L')){
                                insert(i);
                                break;
                            }
                        }
                        for(int i=0;i<(int)s.size()-1;i++){
                            if(check(i,'I')){
                                insert(i);
                                break;
                            }
                        }
                        for(int i=0;i<(int)s.size();i++){
                            if(check(i,'T')){
                                insert(i);
                                break;
                            }
                        }
                        for(int i=0;i<(int)s.size()-1;i++){
                            if(check(i,'I')){
                                insert(i);
                                break;
                            }
                        }
                    }
                }
            }else if(b[2]<b[0]&&b[2]<b[1]){
                do{
                    f=0;
                    for(int i=0;i<(int)s.size()-1;i++){
                        if(check(i,'T')){
                            f=1;
                            insert(i);
                            break;
                        }
                    }
                }while(b[2]<b[0]&&b[2]<b[1]&&f);
                while(b[2]<b[0]&&b[2]<b[1]){
                    p=-1;
                    for(int i=0;i<(int)s.size()-1;i++){
                        if(check(i,'L')){
                            p=i;
                            break;
                        }
                    }
                    if(p==-1){
                        for(int i=0;i<(int)s.size();i++){
                            if(check(i,'I')){
                                insert(i);
                                break;
                            }
                        }
                        for(int i=0;i<(int)s.size()-1;i++){
                            if(check(i,'T')){
                                insert(i);
                                break;
                            }
                        }
                        for(int i=0;i<(int)s.size();i++){
                            if(check(i,'L')){
                                insert(i);
                                break;
                            }
                        }
                        for(int i=0;i<(int)s.size()-1;i++){
                            if(check(i,'T')){
                                insert(i);
                                break;
                            }
                        }
                    }else{
                        for(int i=0;i<(int)s.size();i++){
                            if(check(i,'L')){
                                insert(i);
                                break;
                            }
                        }
                        for(int i=0;i<(int)s.size()-1;i++){
                            if(check(i,'T')){
                                insert(i);
                 c               break;
                            }
                        }
                        for(int i=0;i<(int)s.size();i++){
                            if(check(i,'I')){
                                insert(i);
                                break;
                            }
                        }
                        for(int i=0;i<(int)s.size()-1;i++){
                            if(check(i,'T')){
                                insert(i);
                                break;
                            }
                        }
                    }
                }
            }
            cout<<q.size()<<'\n';
            while(!q.empty()){
                cout<<q.front()<<'\n';
                q.pop();
            }
        }
    }
    return 0;
}