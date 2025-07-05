#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://www.nowcoder.com/practice/e7ed657974934a30b2010046536a5372
class DSU{
private:
    vector<int> fa, siz;
public:
    DSU () {}
    DSU (int n) {
        fa.resize(n);
        iota(fa.begin(), fa.end(), 0);
        siz.assign(n, 1);
    }
    int find(int x) {
        while(x != fa[x]) {
            x = fa[x] = fa[fa[x]];
        }
        return x;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool merge(int x, int y){
        x = find(x);
        y = find(y);
        if(x == y) {
            return false;
        }
        siz[x] += siz[y];
        fa[y] = x;
        return true;
    }
    int size(int x) {
        return siz[find(x)];
    }
};
void solve(){
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    for(int i = 0; i < m; i++){
        int flag, x, y;
        cin >> flag >> x >> y;
        if(flag == 1) {
            if(dsu.same(x, y)) {
                cout << "Yes\n";
            }else{
                cout << "No\n";
            }
        }
        else if(flag == 2) {
            dsu.merge(x, y);
        }
    }    
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

