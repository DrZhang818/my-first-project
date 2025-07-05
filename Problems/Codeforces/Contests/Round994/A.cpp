#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/2049/problem/A
/*
    贪心思维
    题意:
        给定一个长度为n的数组, 你可以对数组进行以下操作
        op: 选定一段子数组, 将这一段替换为子数组中没有出现的最小非负整数
        目标是求出使数组元素全部为0的最小操作次数
    关键思考:
        注意到以下性质
            1.区间内不含0, 得到的mex一定是0
            2.区间内含0, 得到的mex一定是个正数
        根据以上性质可以采取以下贪心策略:
            选取第一个正数作为左端点, 最后一个正数为右端点
            如果区间内有0, 可以通过一次操作将l+1 -> r的位置变成一个正数, 再进行一次变为0
            如果区间内没有0, 则可以直接将l -> r变为0
            如果整个数组没有正数, 答案就是0 
*/
//优化写法
void solve1(){
    int n;
    cin >> n;
    vector<int> nums(n);
    for(auto &num : nums) cin >> num;
    int l = -1, r = -1, flag = INT_MAX;
    for(int i = 0; i < nums.size(); i++){
        if(nums[i]){
            r = i;
            if(l == -1) l = i;
        }
        else if(l != -1 && flag == INT_MAX) flag = i;
    }
    if(l == -1) cout << 0 << "\n";
    else cout << (flag < r ? 2 : 1) << "\n";
}
//比赛时写法
void solve(){
    int n;
    cin >> n;
    vector<int> nums(n);
    for(auto &x : nums){
        cin >> x;
    }
    int ans = 0;
    int l = 0, r = n - 1;
    while(l < n && nums[l] == 0){
        l++;
    }
    while(r >= 0 && nums[r] == 0){
        r--;
    }
    if(l == r){
        cout << 1 << "\n";
        return ;
    }
    if(l == n && r == -1){
        cout << 0 << "\n";
        return ;
    }
    bool ok = false;
    for(int i = l; i <= r; i++){
        if(nums[i] == 0){
            ok = true;
        }
    }
    cout << (ok ? "2\n" : "1\n");

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    while(t--){
        solve1();
    }
    return 0;
}
