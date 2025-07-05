#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

/*
    贪心思维 || 栈
    题意: 定义一个数组是简单的, 如果满足a[i] = i(1-index)
        判断给定数组能否由若干个简单数组通过插入的方式获得
    关键思考:
        从右想左贪心
        假设数组是1 2 3 1 2 3 4 5
        那么右端的1是选择1 2 3还是1 2 3 4 5呢?
        假设右端的1不负责4 5, 那么这4 5必然由前面的处理
            此时前面如果有1 2 3, 可以对接
                    如果没有, 会导致答案变劣
        因此从右向左贪心, 每个1处理尽可能长的数组, 最终判断是否有没有处理的即可
    由于是从右向左, 本质是个逆序的过程, 有使用栈的写法(类似合法括号)
*/
//优化做法
void solve1(){
    int n;
    cin >> n;
    vector<int> nums(n);
    for(auto &num : nums) cin >> num;
    stack<int> stk1, stk2;
    int depth = 0, preDepth = 0;
    for(auto num : nums){
        if(num == 1){
            stk1.push(num);
            depth++;
        }
        else{
            if(!stk2.empty() && depth == preDepth){
                stk2.pop();
            }
            stk2.push(num);
            preDepth = depth;
        }
        
    }
    cout << "YES\n";
}
//比赛时做法
void solve(){
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    if (nums[0] != 1) {
        cout << "NO\n";
        return;
    }
    vector<int> idx;
    for (int i = 0; i < n; i++) {
        if (nums[i] == 1) {
            idx.push_back(i);
        }
    }
    vector<int> vis(n, -1);
    for (int p = idx.size() - 1; p >= 0; p--) {
        int i = idx[p];
        int pre = 1;
        for (int j = i + 1; j < nums.size(); ) {
            if (nums[j] == 1) {
                j = vis[j];
            }
            if (j < n && nums[j] - pre == 1) {
                vis[j] = 0;
                pre = nums[j];
                j++;
            } else {
                vis[i] = j;
                break;
            }
        }
        if (vis[i] == -1){
            vis[i] = n;
        }
    }
   
    for (int i = 0; i < n; i++) {
        if (vis[i] == -1) {
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
        solve1();
    }
    return 0;
}