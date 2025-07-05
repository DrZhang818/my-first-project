#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://leetcode.cn/problems/count-beautiful-splits-in-an-array/description/
/*
    LCP数组 || Z函数(扩展ZMP)
    lcp[i][j] := 后缀 nums[i:] 和后缀 nums[j:] 的最长公共前缀（Longest Common Prefix）的长度。
    初始状态: lcp[i][j] = 0
    状态转移: if nums[i] == nums[j]
                lcp[i][j] = lcp[i + 1][j + 1] + 1
              else
                lcp[i][j] = 0 (可省略else)
    求分割数目:即求方案数问题, 用ans统计即可

*/
void solve1(){
    int n;
    cin >> n;
    vector<int> nums(n);
    for(auto& num : nums) cin >> num;     
    vector<vector<int>> lcp(n + 1, vector<int>(n + 1));
    for(int i = n - 1; i >= 0; i--){
        for(int j = n - 1; j >= 0; j--){
            if(nums[i] == nums[j]){
                lcp[i][j] = lcp[i + 1][j + 1] + 1;
            }
        }
    }
    int ans = 0;
    for(int i = 1; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            if(i <= j - i && lcp[0][i] >= i || lcp[i][j] >= j - i){
                ans++;
            }
        }
    }
    cout << ans << "\n";
}
//z函数
void z_algorithm(vector<int> &z, const vector<int>& s, int idx) {
    int n = s.size();
    z[0] = n - idx;
    for (int i = 1, c = idx, r = idx, len; i + idx < n; i++) {
        len = r > i + idx ? min(r - i - idx, z[i + idx - c]) : 0;
        while (i + idx + len < n && s[i + idx + len] == s[idx + len]) {
            len++;
        }
        if (i + idx + len > r) {
            r = i + idx + len;
            c = i + idx;
        }
        z[i] = len;
    }
}
void solve2(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int ans = 0;
    vector<int> z1(n), z2(n);
    z_algorithm(z1, a, 0);
    for(int i = 1; i < n - 1; i++){
        z_algorithm(z2, a, i);
        for(int j = i + 1; j < n; j++){
            if(z1[i] >= i && j - i >= i || z2[j - i] >= j - i){
                ans++;
            }
        }
    }
    cout << ans << "\n";
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    while(t--){
        solve2();
    }
    
    return 0;
}
