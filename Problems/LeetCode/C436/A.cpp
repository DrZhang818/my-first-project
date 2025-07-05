#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://leetcode.cn/problems/sort-matrix-by-diagonals/
/*
    模拟 || 矩阵对角线遍历
    题意:
        给定一个n × n的矩阵, 要求按照以下方式调整矩阵
        左下角三角形(包括中间对角线)的对角线按非递增顺序排序。
        右上角三角形 的对角线按非递减顺序排序。
    关键思考:
        只需要按照对角线遍历矩阵收集元素, 排序后再填回即可
        矩阵对角线遍历模板为:
        (1)给对角线编个序号 1 ~ n + m - 1(从右上到左下)
        (2)将矩阵行和列 与 序号直接建立映射关系
            利用j-i为定值, 我们可以这样建立: m - (j - i) == 编号
        (3)枚举j, 利用映射关系推导i, 记编号为s
            j = m + i - s, 其中i ∈ [0, n - 1]
            因此minJ = m - s, maxJ = m + n - 1 - s
            同时注意j ∈ [0, m - 1]
            因此minJ = max(0, m - s)
                maxJ = min(m - 1, m + n - 1 - s)
            i 可以由 i = s + j - m 推导得出
*/  
//优化写法
class Solution1 {
public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& a) {
        int n = a.size(), m = a[0].size();
        for(int s = 1; s < n + m; s++) {
            int minJ = max(0, m - s);
            int maxJ = min(m - 1, n + m - 1 - s);
            vector<int> diag;
            for(int j = minJ; j <= maxJ; j++) {
                int i = s + j - m;
                diag.push_back(a[i][j]);
            }
            if(minJ > 0) {
                sort(diag.begin(), diag.end());
            } else {
                sort(diag.begin(), diag.end(), greater<int>());
            }
            int idx = 0;
            for(int j = minJ; j <= maxJ; j++) {
                int i = s + j - m;
                a[i][j] = diag[idx++];
            }
        }
        return a;
    }
};


//比赛写法
class Solution {
public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> ans(n, vector<int>(n));
        for(int t = 0; t < n; t++) {
                vector<int> temp;
            for(int i = t; i < n; i++) {
                temp.push_back(grid[i][i - t]);
                sort(temp.begin(), temp.end(), greater<int>());
                for(int j = 0; j < temp.size(); j++) {
                    ans[i][i - t] = temp[j];
                }
            }      
        }
        for(int t = 0; t < n - 1; t++) {
                vector<int> temp;
            for(int i = 0; i < n - 1 - t; i++) {
                temp.push_back(grid[i][i - t + 1]);
                sort(temp.begin(), temp.end(), greater<int>());
                for(int j = 0; j < temp.size(); j++) {
                    ans[i][i - t + 1] = temp[j];
                }
            }      
        }     
        return ans;
    }
};