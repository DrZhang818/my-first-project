#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://www.luogu.com.cn/problem/P10426
/*
    数论 
    题意:
        给定一个长度为n的数组, 定义一个三元组(x,y,z)的权值为:
        S = x*y*z*LCM(x,y,z) / (LCM(x,y)*LCM(y,z)*LCM(x,z))
        要求计算出权值最大的三元组, 如果有多个权值最大的, 输出排序后字典序最小的方案
        范围: n∈[3,1e5], a[i]∈[1,1e5]
    关键思考:
        本题是决策类题目, 常用思考方式为: 暴力->贪心||DP, 常用优化手段为: 前缀和、双指针、数据结构
        暴力的做法就是枚举每个三元组, 分别计算权值, 时间复杂度大于O(n^3), 需要优化
        优化的手段是利用数学方法对权值计算方法进行化简
        由唯一分解定理, 我们可以设x = ∏pi^ai, y = ∏pi^bi, z = ∏pi^ci
        则LCM(x,y,z) = ∏pi^max(ai,bi,ci)
        LCM(x,y) = ∏pi^max(ai,bi), LCM(x,z) = ∏pi^max(ai,ci), LCM(y,z) = ∏pi^max(bi,ci)
        不妨设ai <= bi <= ci
        则LCM(x,y,z) = ∏pi^ci, LCM(x,y) = ∏pi^bi, LCM(x,z) = ∏pi^ci, LCM(y,z) = ∏pi^ci
        那么式子就化简为∏pi^(ai + bi + ci + ci - bi - ci - ci) = ∏pi^ai
        而我们可以继续变形, ai = min(ai,bi,ci)
        而∏pi^min(ai,bi,ci) 就等于 gcd(x,y,z)
        因此问题最终转化为求解一个三元组使得gcd最大
        这是个经典的问题, 我们可以借鉴埃氏筛的想法, 利用调和级数trick在O(nlogn)的时间内解决
        只需要倒序枚举[1,MX]内的数字j能否成为答案, 即只要找到至少三个数包含因子j, 那么就是合法方案
        注意题目的一个坑: 数组内的数字是可重复的, 因此我们需要记录每个数字的次数, 因为同一个数
        可以多次贡献
*/
void solve() { 
    int n;
    cin >> n;
    vector<int> a(n + 1);
    int mx = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        mx = a[i] > mx ? a[i] : mx;
    }   
    int x = -1, y = -1, z = -1;
    vector<int> b(mx + 1);
    for(int i = 1; i <= n; i++) {
        b[a[i]] += 1;
    }
    for(int i = mx; i > 0; i--) {
        int cnt = 0;
        for(int j = i; j <= mx; j += i) {
            if(b[j]) {
                cnt += b[j];
            }
        }
        if(cnt >= 3) {
            for(int j = i; j <= mx; j += i) {
                while(b[j]) {
                    if(x == -1) x = j;
                    else if(y == -1) y = j;
                    else if(z == -1) {
                        z = j;
                        cout << x << " " << y << " " << z << "\n";
                        return;
                    }
                    b[j] -= 1;
                }
            }
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
    
