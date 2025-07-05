#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://codeforces.com/contest/2048/problem/D
/*
    贪心思维
    题意:
        给定长度为n的数组nums1和长度为m的数组nums2, 你需要按照某种方式将nums2划分成
        m // k组, 对于每一组arr, 定义它的权值为: 数组nums1中的首元素的排名
        排名的方式为: arr中小于等于x的个数为x的权值, 排名由权值大小决定
        现在, 你需要求出在最优划分下, 这m // k组arr的权值之和为多少
        对于k = 1,2,...,m 分别求出答案并输出
    

*/
void solve(){
    int n, m;
    cin >> n >> m;
    int my;
    vector<int> nums(n), help;
    for(int i = 0; i < n; i++){
        cin >> nums[i];
        if(i == 0){
            my = nums[i];
        }
        if(i != 0 && nums[i] > my){
            help.push_back(nums[i]);
        }
    }
    vector<int> c(m);
    for(int i = 0; i < m; i++){
        cin >> c[i];
    }
    sort(help.begin(), help.end());
    for(int i = 0; i < m; i++){
        if(c[i] <= my){
            c[i] = 1;
        }
        else{
            int count = help.end() - lower_bound(help.begin(), help.end(), c[i]);
            c[i] = 1 + count;
        }
    }
    sort(c.begin(), c.end());
    
    for(int i = 1; i <= m; i++){
        ll sum = 0;
        for(int j = i - 1; j < m; j += i){
            sum += c[j];
        }
        cout << sum << " ";
    }
    cout << "\n";
    
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
