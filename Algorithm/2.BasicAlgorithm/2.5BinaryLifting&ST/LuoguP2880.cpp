#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://www.luogu.com.cn/problem/P2880
/*
    ST表 
    题意:
        给定一个长度为n的数组, 现在需要回答q组询问:
        q: 给定l,r, 回答区间[l,r]的极差
        范围: n∈[1,5e4], ai∈[1,1e6], i∈[1,n], q∈[1,1.8e5]
    关键思考:
        本题属于数据结构类裸题, 需要根据题目需要来设计
        对于本题是个静态系统(不带修), 只需要做到区间最值查询即可
        这是经典的RMQ问题, 可以利用ST表进行维护, 可以做到O(1)查询
        (1)预处理ST表:
        利用DP思想来计算即可, 以维护最大值为例
        定义mx[i][s] := 以i为左端点, 长度为2^s的区间内的最大值
        状态初值: mx[i][0] = a[i]
        状态转移: mx[i][s] = max(mx[i][s - 1], mx[i + (1 << s - 1)][s - 1])
        (2)回答询问:
        RMQ问题的本质是可重复贡献问题, 即只要求不漏, 不要求不重
        查询的时候对len进行划分, 我们要找到最大的s满足2^s <= len
        那么s就等于log2(len)
        为了加速log计算, 我们可以预处理出lg数组, 方法为
        初值: lg[1] = 0
        状态转移: lg[i] = lg[i >> 1] + 1
*/
void solve(){
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int N = log2(n); 
    vector<vector<int>> mx(n + 1, vector<int>(N + 1)), mn(n + 1, vector<int>(N + 1));
    for(int i = 1; i <= n; i++) {
        mx[i][0] = mn[i][0] = a[i];
    }
    for(int s = 1; s <= N; s++) { 
        for(int i = 1; i + (1 << s - 1) <= n; i++) { 
            mx[i][s] = max(mx[i][s - 1], mx[i + (1 << s - 1)][s - 1]);
            mn[i][s] = min(mn[i][s - 1], mn[i + (1 << s - 1)][s - 1]);
        }
    }
    vector<int> lg(n + 1);
    lg[1] = 0;
    for (int i = 2; i <= n; i++) {
        lg[i] = lg[i >> 1] + 1;
    }
    while(q--) {
        int a, b;
        cin >> a >> b;
        int len = b - a + 1;
        int s = lg[len];
        int hi = max(mx[a][s], mx[b - (1 << s) + 1][s]);
        int lo = min(mn[a][s], mn[b - (1 << s) + 1][s]);
        cout << hi - lo << "\n";
    }   
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
