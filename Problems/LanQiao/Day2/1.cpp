#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://www.lanqiao.cn/problems/20103/learning/?contest_id=236
/*
    贪心思维 || 频率统计
    题意:
        给定一个长度为n的数组, 你需要从数组中选出一个合法子序列, 问子序列长度最大为多少
        一个子序列是合法的, 如果满足该序列重排后能变成先严格递增再严格递减的数组
    关键思考:
        贪心地想, 要让长度最大, 一定是能选就选, 容易得到以下性质
        (1)两个不同的数一定有大小关系, 因此当a != b时, 选取a不会影响选取b
        (2)两个相同的数至多选两次, 因为最多在递增出现一次, 在递减出现一次
        (3)最大值一定只能选一次, 因为这是递增递减交接的部分
    代码实现:
        需要一个数据结构实现统计选取次数和查找最大值, 因此使用map即可
*/
void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    map<int,int> mp;
    int c = 0;
    for(auto &x : a) cin >> x;
    for(int i = 0; i < n; i++){
        if(mp[a[i]] < 2){
            mp[a[i]]++;
            c++;
        }
    }
    PII pos = *mp.rbegin();
    if(pos.second == 2) c--;
    cout << c << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}