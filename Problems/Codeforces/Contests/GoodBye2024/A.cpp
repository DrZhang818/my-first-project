#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/2053/problem/A
/*
    贪心思维
    题意:
        给定一个数组, 你的任务是对数组进行任意划分, 使得每个子数组满足
        从子数组任意选三个数(可能是同一个数), 都能构成三角形
        判断是否存在至少两个不同的划分方式
    关键思考:
        (1)显然, 每两个数之间都进行划分, 这样任意子数组只由一个元素构成, 那么必然可以组成
           等边三角形, 因此是合法划分
        (2)子数组内元素越少, 越可能满足合法性, 因此在(1)的基础上查看是否存在一个长度为2的
           子数组满足性质
           即只需要判断是否存在一个长度为2的数组满足
           2*min > max
*/
void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n - 1; i++){
        int t = min(a[i], a[i + 1]);
        int q = max(a[i], a[i + 1]);
        if(2 * t > q){
            cout << "Yes\n";
            return ;
        }
    }
    cout << "No\n";
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
