#include "../code/gauss.hpp"
int main() {
    const int P = 101, n = 3, m = 2;
    vector<vector<int>> a = {{0, 0, 0, 0}, {0, 1, 2, 5}, {0, 2, 100, 0}, {0, 3, 1, 5}};
    vector<int> w;
    int r = gaussMod(a, P, w);
    bool ok = true;
    for(int i = r + 1; i <= n; i++) {
        if(a[i][m + 1]) {
            ok = false;
        }
    }
    assert(ok);
    vector<int> x(m + 1); // 自由变量取0。
    for(int j = 1; j <= m; j++) {
        if(w[j]) {
            x[j] = a[w[j]][m + 1];
        }
    }
    assert(x[1] == 1 && x[2] == 2);
}
