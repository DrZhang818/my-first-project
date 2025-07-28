#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://leetcode.cn/problems/count-number-of-trapezoids-ii/description/
/*
    枚举 || 计算几何
    题意:
        给定二维平面上的N个点, 你可以从中任选四个点并连成一个凸四边形, 求解有多少种方案可以
        组成梯形
        两种方案被认为是不同的, 当且仅当两种方案选择的点集不同
        范围: N∈[4,500], x,y∈[-1000,1000]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 前缀和、双指针、数学
        计数类问题我们要找到便于计数的划分方式, 找到合适的枚举变量
        对于梯形来说, 最核心的几何性质为: 存在至少一对平行边
        我们可以在O(N^2)的时间内枚举所有点对的斜率, 把斜率相同的分到相同的组, 显然答案只会在同一组内
        产生
        另一个问题是共线, 如果两条线段共线, 即使斜率是一样的, 也不能组成梯形
        因此, 在同一组内还需要按照截距再次分组
        特判线段平行y轴的情况, 此时可以人为规定一下, 令斜率为无穷大, 截距为横截距
        这样设定的原因很简单, 我们只要能保证不重不漏, 就是合法的设定
        然而, 这样统计出的答案还是会重复:
            对于平行四边形, 两组对边都是平行的, 于是会被统计两次
        因此, 我们还需要统计出平行四边形的数量, 减掉之后才是真正的梯形数量
        平行四边形的核心性质是: 两条对角线的中点重合
        因此我们可以按照中点进行分组, 同样的问题, 我们还是需要去掉共线的情况
        此时, 我们可以按斜率进行分组, 两条斜率不一样的直线必然不会共线
        于是我们得到以下算法:
            对于梯形, 按斜率 + 截距分组
            对于平行四边形, 按中点 + 斜率分组
        下面是细节讨论:
        (1)
            什么时候double不能作为map/umap的key
            根据IEEE 754, 当数据范围在2^26(6.7e7)以内时, 可以作为key
            如果超过这个范围, 我们就需要用既约分数了
        (2)
            关于平行四边形的中点
            我们可以乘2, 避免浮点数误差
            此外为了方便存到umap, 我们把x,y压成一维
            压维必须保证同正, 我们必须做偏移量
            带负数的位运算会出现问题
*/
class Solution {
public:
    int countTrapezoids(vector<vector<int>>& P) {
        int n = P.size();
        unordered_map<db,vector<db>> mp1;
        unordered_map<int,vector<db>> mp2;
        for(int i = 0; i < n; i++) {
            int x1 = P[i][0], y1 = P[i][1];
            for(int j = 0; j < i; j++) {
                int x2 = P[j][0], y2 = P[j][1];
                int dx = x1 - x2, dy = y1 - y2;
                db k = dx ? 1.0 * dy / dx : DBL_MAX;
                db b = dx ? 1.0 * (y1 * dx - x1 * dy) / dx : x1;
                mp1[k].push_back(b);
                int mid = (x1 + x2 + 2000) << 16 | (y1 + y2 + 2000);
                mp2[mid].push_back(k);
            }
        }
        int ans = 0;
        for(auto &[_, g] : mp1) {
            if(g.size() == 1) continue;
            map<db,int> m;
            for(db b : g) {
                m[b]++;
            }
            int tot = 0;
            for(auto &[_, c] : m) {
                ans += tot * c;
                tot += c;
            }
        }
        for(auto &[_, g] : mp2) {
            if(g.size() == 1) continue;
            map<db,int> m;
            for(db k : g) {
                m[k]++;
            }
            int tot = 0;
            for(auto &[_, c] : m) {
                ans -= tot * c;
                tot += c;
            }
        }
        return ans;
    }
};