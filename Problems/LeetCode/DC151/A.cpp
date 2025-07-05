#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://leetcode.cn/problems/transform-array-by-parity/description//
/*
    模拟
    题意:
        给定一个长度为N的数组, 你需要将每个偶数替换为0, 将每个奇数替换为1
        并按非递减顺序输出修改后的数组
    关键思考:
        本题为模拟类题目, 需要选择合适的算法与数据结构维护题目的信息
        本题由于要排序, 所以我们可以利用计数排序思想, 统计0和1的个数即可
*/
class Solution {
public:
    vector<int> transformArray(vector<int>& a) {
        vector<int> ans(a.size());
        int c0, c1;
        for(auto c : a) {
            c0 += c % 2 == 0;
            c1 += c % 2 == 1;
        }
        for(int i = 0; i < a.size(); i++) {
            a[i] = c0 == 0 ? 0 : 1;
            c0 -= 1;
            c1 -= 1;
        }
        return ans;
    }
};