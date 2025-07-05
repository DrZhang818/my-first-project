#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://www.luogu.com.cn/problem/P3389
/*
    数学 || 模拟
    题意:
        给定一个n元线性方程组, 求解方程组的解, 无解输出"No Solution"
    关键思考:
        本题为计算&模拟类题目, 常用方法为通过数学推导来优化复杂度, 使用合适的算法与数据结构维护信息
        本题为高斯消元法的模板, 下面给出求解过程
        (1)选取主元(满足i == j的称为主元)
        (2)把主元换到当前行
        (3)归一化当前行
        (4)消去其他行的当前列
*/
constexpr db EPS = 1e-7;
void solve() { 
    int n;
    cin >> n;
    vector<vector<db>> a(n + 1, vector<db>(n + 2));
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n + 1; j++) cin >> a[i][j];
    for(int i = 1; i <= n; i++) {
        int mx = i;
        for(int k = i + 1; k <= n; k++) {
            if(fabs(a[k][i]) > fabs(a[mx][i])) {
                mx = k;
            }
        }
        if(fabs(a[mx][i]) < EPS) {
            cout << "No Solution\n";
            return;
        }
        swap(a[i], a[mx]);
        for(int j = i + 1; j <= n + 1; j++) {
            a[i][j] /= a[i][i];
        }
        a[i][i] = 1.0;
        for(int k = 1; k <= n; k++) {
            if(k != i) {
                db fac = a[k][i];
                for(int j = i; j <= n + 1; j++) {
                    a[k][j] -= fac * a[i][j];
                }
                a[k][i] = 0;
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << fixed << setprecision(2) << a[i][n + 1] << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
