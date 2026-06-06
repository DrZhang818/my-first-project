#include <bits/stdc++.h>
using namespace std;
int k,n;
__int128 d[26][26],l=1000000000000000000;
pair<int,int>p[26];
string s[100001], t[3];
struct matrix {
    __int128 v[26][26];
    matrix(){
        for(int i=0;i<26;i++){
            for(int j=0;j<26;j++){
                v[i][j]=1000000000000000000;
            }
        }
    }
    friend matrix operator*(const matrix &X,const matrix &Y){
        matrix Z;
        for(int i=0;i<26;i++){
            for(int j=0;j<26;j++){
                for(int k=0;k<26;k++){
                    Z.v[i][j]=min(Z.v[i][j],X.v[i][k]+Y.v[k][j]);
                }
            }
        }
        return Z;
    }
}A,B;
matrix ksm(matrix X,int y){
    if(y==1) return X;
    matrix Z=X;
    y--;
    while(y){
        if(y&1){
            Z=Z*X;
        }
        X=X*X;
        y>>=1;
    }
    return Z;
}
int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> s[i]; 
    }
    getline(cin, t[0]);
    getline(cin, t[0]);
    assert(t[0].size() == 9);
    getline(cin, t[1]);
    assert(t[0].size() == 9);
    getline(cin, t[2]);
    assert(t[0].size() == 9);
    for(int i=0;i<3;i++){
        for(int j=0;j<9;j++){
            if(islower(t[i][j])){
                p[t[i][j]-'a']=make_pair(i,j);
            }
        }
    }
    for(int i=0;i<26;i++){
        for(int j=0;j<26;j++){
            d[i][j]=abs(p[i].first-p[j].first)+abs(p[i].second-p[j].second);
        }
    }
    for(int i=1;i<=n;i++){
        __int128 w=0;
        for(int j=1;j<s[i].size();j++){
            w+=d[s[i][j-1]-'a'][s[i][j]-'a'];
        }
        for(int j=0;j<26;j++){
            A.v[j][s[i].back()-'a']=min(A.v[j][s[i].back()-'a'],d[j][s[i][0]-'a']+w);
        }
    }
    for(int j=0;j<26;j++){
        B.v[0][j]=0;
    }

    B=B*ksm(A,k);
    for(int j=0;j<26;j++){
        l=min(B.v[0][j],l);
    }
    cout<<(long long)l<<'\n';
    return 0;
}