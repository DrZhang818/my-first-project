#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



/*
    这里的遍历序默认是行从小到大, 列从小到大
    如果想改变列的遍历序, 只需要把minJ -> maxJ改为maxJ -> minJ
    如果想改变行的遍历序, 只需要把s从1 -> n + m - 1调整为n + m - 1 -> 1 
*/
/*
    按主对角线遍历————"\"型遍历
    (1)给对角线编个序号 1 ~ n + m - 1(从右上到左下)
    (2)将矩阵行和列 与 序号直接建立映射关系
        利用j-i为定值, 我们可以这样建立: m - (j - i) == 编号
    (3)枚举j, 利用映射关系推导i, 记编号为s
        j = m + i - s, 其中i ∈ [1, n]
        因此minJ = m - s + 1, maxJ = m + n - s
        同时注意j ∈ [1, m]
        因此minJ = max(1, m + 1 - s)
            maxJ = min(m, m + n - s)
        i 可以由 i = s + j - m 推导得出
*/
void solve1(vector<vector<int>>& a) {
    int n = a.size() - 1, m = a[0].size() - 1;
    for(int s = 1; s < n + m; s++) {
        int minJ = max(1, m + 1 - s);
        int maxJ = min(m, m + n - s);
        for(int j = minJ; j <= maxJ; j++) {
            int i = s + j - m;
            cout << a[i][j] << " ";
        }
        cout << "\n";
    } 
}

/*
    按主对角线遍历————"/"型遍历
    (1)给对角线编个序号 1 ~ n + m - 1(从左上到右下)
    (2)将矩阵行和列 与 序号直接建立映射关系
        利用j+i为定值, 我们可以这样建立: i + j - 1 == 编号
    (3)枚举j, 利用映射关系推导i, 记编号为s
        j = s - i + 1, 其中i ∈ [1, n]
        因此minJ = s - n + 1, maxJ = s
        同时注意j ∈ [1, m]
        因此minJ = max(1, s - n + 1)
            maxJ = min(m, s)
        i 可以由 i = s - j + 1 推导得出
*/
void solve2(vector<vector<int>>& a) {
    int n = a.size() - 1, m = a[0].size() - 1;
    for(int s = 1; s < n + m; s++) {
        int minJ = max(1, s - n + 1);
        int maxJ = min(m, s);
        for(int j = minJ; j <= maxJ; j++) {
            int i = s - j + 1;
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> grid[i][j];
        }
    }

    solve1(grid);
    cout << "\n";
    solve2(grid);
    return 0;
}