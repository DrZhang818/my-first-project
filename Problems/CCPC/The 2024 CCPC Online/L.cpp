#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
char a[600][600];
inline bool ck(int i,int j)
{
    return a[i][j]=='c'&&a[i][j+1]=='c'&&a[i+1][j]=='p'&&a[i+1][j+1]=='c';
}
int n,m;
void solve() {
        cin>>n>>m;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)cin>>a[i][j];
    }
    int ans=0;
    for(int i=1;i<=n-1;++i)
    {
        for(int j=1;j<=m-1;++j)
        {
            if(ck(i,j))ans++;
        }
    }
    cout<<ans;
}       

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    return solve(),0;
}
