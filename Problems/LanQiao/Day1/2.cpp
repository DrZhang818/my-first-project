#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://www.lanqiao.cn/problems/5167/learning/?contest_id=235
/*
    滑动窗口(越短越合法) || 单调队列
    题意:
        给定长度为n的数组和一个整数k, 要求计算出长度大于等于2并且极差小于等于k的子数组个数
    关键思考:
        本题是很经典的子数组计数问题, 观察后容易发现满足以下单调性:
            当[l,...,r]是一个合法子数组时, [l+1,...,r]显然也是合法的
        因此采用不定长滑窗即可解决, 在枚举右端点时维护窗口内最大值和最小值
        由于涉及窗口内最大最小值, 因此需要使用单调队列这个数据结构来实现
    代码实现:
        优先队列经典模板:入队, 出队, 更新答案
        入队: pop队尾比当前值大(小)的值, 然后当前元素入队
        出队: 当前窗口最大值与最小值大于k时, 需要出队
              出队时选择更靠左的最大值/最小值并弹出
              然后更新左指针l为更靠左最大值/最小值
              持续此过程直到窗口合法为止
        更新答案:
              ans += r - l即可
              注意区间长度为1不合法, 因此是r-l而不是r-l+1
*/
void solve(){
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    deque<int> qm, qn;
    int ans = 0;
    int l = 0;
    for(int r = 0; r < n; r++){
        while(!qm.empty() && a[qm.back()] <= a[r]){
            qm.pop_back();
        }
        qm.push_back(r);
        while(!qn.empty() && a[qn.back()] >= a[r]){
            qn.pop_back();
        }
        qn.push_back(r);
        while(!qm.empty() && !qn.empty() && a[qm.front()] - a[qn.front()] > k){
            if(qm.front() < qn.front()){
                qm.pop_front();
            }else{
                qn.pop_front();
            }
            l = min(qm.front(), qn.front());
        }
        ans += r - l;
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}