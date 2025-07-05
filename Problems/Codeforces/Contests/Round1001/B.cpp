#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/2062/problem/B
/*
    贪心
    题意:
        给定一个长为n的数组, 每秒会按顺序发生以下事件:
        (1)所有元素-1, 如果某个元素变为0则失败
        (2)保持当前位置或者移动到相邻位置
        (3)将当前元素的值重置为初始数组时的值
        你可以任选一个位置作为初始位置
        问能否有种策略使得游戏能够无限进行(即保持所有元素恒正)
    关键思考:
        必要性:
            思考以下情况
            [@..*....#]
            由于#迟早会降为0, 因此一定有一次移动是*->#, 而由于*也需要维持, 所以到达#后也一定会回到*
            因此最省时间的方式就是直线移动: * -> # -> *, 这就要求*必须能够坚持住一来一回
            左侧@同理
            因此*必须坚持住max(左侧来回, 右侧来回)
            对于任意元素同理
            一来一回的时间是2*len
            因此每个元素必须满足a[i] > 2 * len
        充分性:
            如果每个元素都满足a[i] > 2 * len, 是否一定能够持续进行呢?
            这是一定的
            不管从哪里起始, 都可以满足
            例如从左端点起始, 一直向右走, 到达右端点再返回
            这样第i个元素需要坚持 max(i, 2 * i, 2 * (n - 1 - i))
            因为一定有i <= 2 * i
            所以最大值就是max(2 * i, 2 * (n - 1 - i)), 这正是上面求出来的2 * len
*/
void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n; i++){
        int dis = max(2 * (n - 1 - i), 2 * i);
        if(a[i] <= dis){
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);


    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}