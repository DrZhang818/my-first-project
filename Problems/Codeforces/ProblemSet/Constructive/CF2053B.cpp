#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/2053/problem/B
/*
    构造 || 前缀和 || 频率统计
    题意:
        给你一个整数n和n个线段, 第i个线段表示第i个点可能出现的范围为[li,ri]
        依次判断1~n的每个点能否成为独特的, 一个点是独特的, 如果满足:
        存在一种合法方案, 使得构造出的数组中, a[i]这个数是唯一出现的
    关键思考:
        如果l == r, 这种点是唯一确定的, 把这些点记录下来
        在判断的时候, 只需要判断[li,ri]内确定的点的个数(去重)是否小于区间长度
        特判: 如果li == ri, 需要判断在该点唯一确定的个数是否恰好为1 
*/
//优化写法
void solve1(){
    int n;
    cin >> n;
    vector<int> l(n), r(n);
    vector<int> cnt(2 * n), pre(2 * n + 1);
    for(int i = 0; i < n; i++){
        cin >> l[i] >> r[i];
        l[i]--;
        if(l[i] + 1 == r[i]){
            cnt[l[i]]++;
        }
    }
    for(int i = 0; i < 2 * n; i++){
        pre[i + 1] = pre[i] + (cnt[i] == 0);
    }
    for(int i = 0; i < n; i++){
        if(l[i] + 1 < r[i]){
            cout << (pre[l[i]] != pre[r[i]]);
        }else{
            cout << (cnt[l[i]] == 1);
        }
    }
    cout << "\n";
}
//比赛做法
void solve(){
    int n;
    cin >> n;
    vector<int> vis(2 * n + 1);
    vector<PII> nums(n);
    for(int i = 0; i < n; i++){
        int l, r;
        cin >> l >> r;
        nums[i].first = l;
        nums[i].second = r;
        if(l == r){
            vis[l]++;
        }
    }
    vector<int> pre(2 * n + 2);
    for(int i = 1; i < pre.size(); i++){
        pre[i] = pre[i - 1] + (vis[i] != 0);
    }
    for(int i = 0; i < n; i++){
        int len = nums[i].second - nums[i].first + 1;
        int l = nums[i].first, r = nums[i].second;
        if(pre[r] - pre[l - 1] < len){
            cout << 1;
        }else if(l == r && vis[l] == 1){
            cout << 1;
        }else{
            cout << 0;
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
