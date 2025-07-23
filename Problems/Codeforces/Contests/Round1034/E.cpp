#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2123/problem/E
/*
    构造 || 枚举 
    题意:
        给定一个长度为N的数组, 对于每个k∈[0,N-1], 你需要回答:
        Q: 删除恰好k个元素后, MEX(a)有多少可能值    
        范围: N∈[1,2e5], a[i]∈[0,N]
    关键思考:
        本题为构造+计数类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        由于问题与元素的值有关, 因此我们用计数数组cnt来存
        正向思考比较困难, 且时间复杂度过高, 此时我们考虑贡献法
        枚举每个MEX的可能值, 看看删除几个元素可以得到当前的MEX
        由mex的性质, 如果cnt[x] = 0, 那么mex值不可能 > x
        因此我们从小到大枚举x, 统计到第一个cnt[x] = 0后就可以结束计数
        对于0~x, 我们思考最少删除几个元素, 最多删除几个元素
        显然, 为了让mex = x, 我们必须把cnt[x]个元素全部删除
        而我们也不能删太多, 必须保证0~x-1也存在
        因此最多删除N-x个元素
        对于[lo,hi]之间的删除个数, 我们显然可以构造解, 只要保证把cnt[x]全部删除且保留0~x-1即可
        因此删除个数在[lo,hi]的可能值 + 1
        利用差分 + 前缀和即可完成统计
*/
void solve() {
    int n;
    cin >> n;
    vector<int> cnt(n + 2);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    vector<int> ans(n + 2);
    for(int i = 0; i <= n; i++) {
        ans[cnt[i]]++;
        ans[n - i + 1]--;
        if(cnt[i] == 0) break;
    }   
    for(int i = 1; i <= n; i++) {
        ans[i] += ans[i - 1];
    }
    for(int i = 0; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

