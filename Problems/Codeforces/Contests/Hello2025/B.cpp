#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

/*struct custom_hash {
    static uint64_t FIXED_RANDOM;

    size_t operator()(const int& key) const {
        return hash<int>()(key) ^ FIXED_RANDOM;
    }
};
uint64_t custom_hash::FIXED_RANDOM = 
    chrono::steady_clock::now().time_since_epoch().count();
*/
//https://codeforces.com/contest/2057/problem/B
/*
    贪心 || 排序 || 频率统计
    题意:
        给你一个长度为n的数组, 你可以进行k次操作
        op1: 修改数组任意位置的值
        操作后, 进行一下新的操作
        op2: 选择一个子数组, 删除其中的最小值
        要求计算出最少需要几次op2使得数组为空
    关键思考:
        对于这种问题, 首先思考不操作如何计算
        假设数组有m种数字, op2的实质就是删除数组中的一种数
        由此可得, min(cnt[op2]) <--> min(kinds[nums])
        也就是通过k次op1能让数组最少有几种数, 这就转化为频率统计问题
    注意事项:
        本题使用umap会被cf测试数据卡哈希冲突, 导致TLE, 因此可以使用map来统计
        当然也可以按照法二, 使用排序来统计
*/
void solve(){
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    map<int, int> mp;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        mp[a[i]]++;
    }
    vector<int> cnt;
    for(auto &[_, c] : mp){
        cnt.push_back(c);
    }
    sort(cnt.begin(), cnt.end());
    int ans = cnt.size();
    for(int i = 0; i < cnt.size() - 1; i++){ //注意遍历到size-1, 因为ans至少为1
        if(k >= cnt[i]){
            ans--;
            k -= cnt[i];
        }
    }
    cout << ans << "\n";
}
void solve1(){
    int n, k; 
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int c = 1;
    vector<int> cnt;
    for(int i = 0; i < n - 1; i++){
        if(a[i + 1] == a[i]){
            c++;
        }else{
            cnt.push_back(c);
            c = 1;
        }
    }
    cnt.push_back(c); //注意这句很关键
    sort(cnt.begin(), cnt.end());
    int ans = cnt.size();
    for(int i = 0; i < cnt.size() - 1; i++){
        if(k >= cnt[i]){
            k -= cnt[i];
            ans -= 1;
        }
    }
    cout << ans << "\n";
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
