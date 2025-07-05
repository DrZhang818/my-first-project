#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://codeforces.com/contest/2050/problem/B
/*
    数学 || 思维
    题意: 给定n个数, 判断能否通过以下两个操作使得所有数相同
            对于下标 i : 1 -> n - 2 (0-based)
            op1: nums[i - 1] -= 1 且 nums[i + 1] += 1
            op2: nums[i - 1] += 1 且 nums[i + 1] -= 1
    关键观察:
        每次操作的两个数的下标的奇偶性相同
        因此我们可以把数组按照下标的奇偶性拆成两个子序列
        问题就转化成
            1.每个子序列内部元素相同
            2.两个子序列的元素相同
        对于问题1:
            可以思考成一个连通器, 水流会自然的从高处流到低处, 直到平衡
            那么问题就在于平衡点是否为整数
        对于问题2:
            只需要把两个子序列的平衡点作比较即可
*/
//优化做法
void solve(){
    int n;
    cin >> n;
    ll aver1 = 0, aver2 = 0;
    for(int i = 1; i <= n; i++){
        ll num;
        cin >> num;
        if(i & 1) aver1 += num;
        else aver2 += num;
    } 
    int odd = (n + 1) / 2, even = n / 2;
    if(aver1 % odd == 0 && aver2 % even == 0 && aver1 / odd == aver2 / even){
        cout << "YES\n";
    }
    else{
        cout <<"NO\n";
    }
}

//比赛时做法(模拟)
void solve2(){
    int n;
    cin >> n;
    std::vector<ll> nums(n);
    ll sum = 0;
    for(int i = 0; i < n; i++){
        cin >> nums[i];
        sum += nums[i];
    }
    if((sum % n) != 0){
        cout << "NO\n";
        return ;
    }
    ll tar = sum / n;
    for(int i = 1; i < n - 1; i++){
        if(nums[i - 1] != tar){
            if(nums[i - 1] < tar){
                nums[i + 1] -= tar - nums[i - 1];
                nums[i - 1] = tar;
            }else{
                nums[i + 1] += nums[i - 1] - tar;
                nums[i - 1] = tar;
            }
        }
    }
    
    if(nums[n - 1] == tar && nums[n - 2] == tar){
        cout << "YES\n";
    }else{
        cout << "NO\n";
    }
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