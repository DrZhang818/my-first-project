#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://leetcode.cn/problems/smallest-substring-with-identical-characters-ii/
/*
    字符串 || 二分答案 
    题意:
        给定一个长度为n的二进制字符串, 你可以对字符串进行以下操作
        op:选择一个下标i, 并翻转s[i]
        要求最小化s的最长相同子字符串的长度
    关键思考:
        本题属于最大值最小化问题, 由这个特点要自然想到答案是否具有一定的单调性, 若有,
        则考虑二分答案
        分析本题, 当len越大, 操作numOps次越能符合;len越小, 越不能符合
        而答案的下界为1, 上界为n, 关键就在于如何写出二分的check函数
        思考简单例子:
            假设m=2, 00不用改
                    000最优的策略是改成010(这样既不会与前面叠加也不会与后面叠加)
                    0000最优是0010
                    00000是000010
                    ...
            我们可以发现对于一个长度为k的字串
            如果要让他满足子子串长度<=m, 最少操作k/(m+1)次
            因此遍历所有重复子串并逐一操作即可
        特别注意:
            对于m=1的情况, 以上算法并不成立
            以上算法成立的核心在于新加的分点可以藏在整体子串里面, 从而不会与外界交互
            如果是m=1, 新加的分点一定会与外界交互, 从而导致计算错误
        那么怎么处理这一情况呢?
            虽然m=1不满足以上算法, 但处理方法却很简单
            因为m=1的情况自由度是最少的
            只有010101...以及101010...这两种情况
            可以很容易计算出能否满足m=1

*/
class Solution {
public:
    int minLength(string s, int numOps) {
        int n = s.size();
        auto check = [&](int mid) -> bool{
            int count = 0; 
            if(mid == 1){   
                string t = "01";
                for(int i = 0; i < n; i++){
                    count += s[i] == t[i & 1];    
                }
                count = min(count, n - count);
            }
            else{
                int k = 0;
                for(int i = 0; i < n; i++){
                    k++;
                    if(i == n - 1 || s[i + 1] != s[i]){
                        count += k / (mid + 1);
                        k = 0;
                    }
                }
            }
            return count <= numOps;
        };
        int l = 0, r = n + 1;
        while(l + 1 < r){
            int mid = l + ((r - l) >> 1);
            if(check(mid)){
                r = mid;
            }
            else{
                l = mid;
            }
        }
        return r;
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}