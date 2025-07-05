#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
class DSU {
private:
    vector<int> fa;
    vector<int> siz;
    int K;
public:
    DSU(){}
    DSU(int n) {
        fa.resize(n);
        siz.assign(n, 1);
        K = n;
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) {
        if(x != fa[x]) {
            fa[x] = find(fa[x]);
        }
        return fa[x];
    }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y) {
            return false;
        }
        siz[x] += siz[y];
        fa[y] = x;
        K -= 1;
        return true;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int size(int x) {
        return siz[find(x)];
    }
    int kinds() {
        return K;
    }
};
void solve(){ 
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
