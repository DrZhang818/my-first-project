#include <iostream>
#include <cstdio>

using namespace std;

int n, m;

int f[200001];

int getFa(int x) {
    if(f[x] == x) return x;
    return f[x] = getFa(f[x]);
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1;i <= n;i++) f[i] = i;
    int ans = 0;
    for(int i = 1, u, v;i <= m;i++) {
        scanf("%d%d", &u, &v);
        int uf = getFa(u);
        int vf = getFa(v);
        if(uf != vf) {
            ++ans;
            f[uf] = vf;
        }
    }
    printf("%d\n", ans);
    return 0;
}
