#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
 

//https://codeforces.com/problemset/problem/1375/C
/*
    贪心 || 构造
    题意:
        给你一个1~n的排列, 你可以选择两个相邻的数, 满足a[i] < a[i + 1], 并删除其中一个
        判断能否通过若干次操作, 使得数组长度为1
    关键思考:
        为了尽可能多删除元素, 我们可以考虑以下贪心策略:
        (1)把尽可能小的数留在左边
        (2)把尽可能大的数留在右边
        对于数组[p...m...q]来说
        p, q一定会保留下来
        因为a[0]与a[1]如果可以操作, 就一定有a[0]<a[1], 根据贪心策略一定是保留a[0], 否则a[1]成为
        最左边的数, 导致答案变劣
        同理对与a[n-2]与a[n-1]的操作, 要保留a[n-1]
        此时, 假设排列可以删除, 最后一步一定是p与q的比较, 那么一定有p < q
        那么, 操作会不会到中间就进行不下去了呢?
        考虑中间某一个元素m, 如果m不可被移除, 当且仅当m < p && m > q
        即q < m < p, 而这与p < q矛盾, 故不存在
    因此, 题目等价转化为判断p是否小于q
*/
void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    if(a[0] < a[n - 1]){
        cout << "Yes\n";
    }else{
        cout << "No\n";
    }
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