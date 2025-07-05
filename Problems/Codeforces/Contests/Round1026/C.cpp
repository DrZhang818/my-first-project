#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2110/problem/C
/*
    构造 || 贪心 || DP
    题意:
        给定N个障碍, 每个障碍以[lo,hi]的形式给出, 表示无人机的高度必须在[lo,hi]内才能通过
        现有一个无人机操作序列, 由-1,0,1三种数字组成
        0表示到该障碍时高度不变 
        1表示到该障碍时高度加1
        -1表示该操作还不确定, 需要由你来决定是0还是1
        你需要给出最终的操作序列, 序列中只有0和1组成, 并且按照该序列操作能够通过所有障碍
        如果不存在任何操作序列可以通过所有障碍, 输出-1
        范围: N∈[1,2e5], 0 <= lo <= hi <= N
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        首先观察题目性质, 我们发现无人机的高度是单调不降的, 这是个重要的贪心信号
        由于每步的操作对后续有影响, 我们无法得到简单的局部贪心策略, 并且到每个位置时最优高度
        我们也很难确定
        此时用到一个重要的trick, 找到合法性的下界和上界, 这样利用极端原理和介值定理我们就
        能够得到在每个位置时无人机应有的高度范围[mn,mx]
        对于mn, 由于无人机不会下降, 因此mn是从左到右单调不降的
        对于mx的维护是本题的难点, 由于无人机要通过i及i以后的所有障碍, 因此mx[i]最多是
        min(hi[i:N]), 而由于i以后的某些操作可能已经固定为1, 这意味着实际的mx[i]要更小
        我们用mx[i] := 第i个位置无人机允许的最大高度
        当d[i + 1] = 1时, mx[i] = min(R[i], mx[i + 1] - 1)
        其余情况, mx[i] = min(R[i], mx[i + 1])
        维护好mx[i]后, 构造就比较简单了
        为了满足mn[i], 我们肯定尽可能地把-1设置为1, 但又要保证满足mx[i]
        因此属于一种比较奇妙的构造性贪心, 这种贪心本身照顾到了全局, 正确性无需证明
*/
void solve() {
    int n;
    cin >> n;
    vector<int> d(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> d[i];
    }
    vector<int> L(n + 1), R(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> L[i] >> R[i];
    }
    for(int i = n - 1; i >= 1; i--) {
        if(d[i + 1] == 1) {
            R[i] = min(R[i], R[i + 1] - 1);
        } else {
            R[i] = min(R[i], R[i + 1]);
        }
    }
    int h = 0;
    for(int i = 1; i <= n; i++) {
        if(d[i] == -1) {
            if(h < R[i]) {
                d[i] = 1;
                h += 1;
            } else {
                d[i] = 0;
            }
        } else {
            h += d[i];
        }
        if(h < L[i] || h > R[i]) {
            cout << -1 << "\n";
            return ;
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << d[i] << " \n"[i == n];
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
