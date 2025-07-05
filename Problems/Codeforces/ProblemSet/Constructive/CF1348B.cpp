#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://codeforces.com/contest/1348/problem/B
/*
    构造 || 滑动窗口思想
    题意:
        给定整数n和k, 和一个长度为n的数组。 你可以对数组进行以下操作
        op:在数组任意位置插入一个1~n之间的数组
        要求构造出一种合法方案, 使得每个长度为k的子数组的sum均相等
        输出构造的数组长度和元素值
    关键思考:
        子数组问题联想滑动窗口算法, 本题要我们构造的数组有以下特点
        [______....] (1)
        [.______...] (2)
        由于这两段的和是相等的, 所以(1)的首元素和(2)的尾元素一定相等
        这本质上就是要我们构造出一个以K为周期的数组
        而每段循环节必须包含原数组所有元素(不重复), 否则显然后面会出现一个不在循环节内的数
        所以当数组unique元素个数大于K的时候输出-1
        其他情况, 最简单的处理就是连续构造n个长度为K的数组
        由于unique元素的数量可能小于K, 对于剩余的部分只需要任取1~n中的一个数进行填补即可
*/
//灵神写法
void solve1(){
    int n, k;
    cin >> n >> k;
    vector<int> a;
    vector<bool> vis(n + 1, false);
    int v;
    for(int i = 0; i < n; i++){
        cin >> v;
        if(v >= 1 && v <= n && !vis[v]){
            vis[v] = true;
            a.push_back(v);
        }
    }
    if(a.size() > k){
        cout << "-1\n";
        return;
    }
    while(a.size() < k){
        a.push_back(1);
    }
    cout << ((ll)a.size() * n) << "\n";
    for(int i = 0; i < n; i++){
        for(auto num : a){
            cout << num << " ";
        }
    }
    cout << "\n";
}
void solve(){
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for(auto &c : nums) cin >> c;
    unordered_map<int, int> mp;
    for(int i = 0; i < nums.size(); i++){
        mp[nums[i]]++;
    }    
    if(mp.size() > k){
        cout << -1 << "\n";
        return;
    }
    vector<int> a;
    for(auto &[c, _] : mp){
        a.push_back(c);
    }
    cout << n * k << "\n";
    for(int i = 0; i < n; i++){
        for(int j = 0; j < a.size(); j++){
            cout << a[j] << " ";
        }
        for(int j = 0; j < (k - a.size()); j++){
            cout << n << " ";
        }
    }
    cout << "\n";
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
