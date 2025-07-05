#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://www.marscode.cn/practice/vkjwp462l6q75q?problem_id=7414004855076700204
/*
    状态机DP
    定义状态: dp[i][j] := 从前i个物品中, 装j件物品的最小花费
    初始条件: dp[1][j] = j * data[0]
    状态转移:
            因为每天都会消耗 1 个物品
            因此, 第 i 天的 j, 可以由i - 1天的 j + 1, j, j - 1, ..., 1转移过来
            let n := 第 i 天选 n 个物品

        dp[i][j] = dp[i - 1][j + 1] , dp[i - 1][j] + x, dp[i - 1][j - 1] + 2 * x ...
        dp[i][j] = min(dp[i - 1][j + 1 - n] + n * x) 
                    其中 j + 1 - n >= 1  -> n <= j
                         j + 1 - n <= k  -> n >= j + 1 - k
                        同时 n >= 0 因为不能选负数个物品
                    综上
                        max(0, j + 1 - k) <= n <= j
                        j in range[1, k]

    return dp[n][1]
*/
int solution(int n, int k, vector<int> data) {
    vector<vector<int>> dp(2, vector<int>(k + 1, 0));
    for(int j = 1; j <= k; j++){
        dp[1][j] = j * data[0];
    }
    for(int i = 2; i <= n; i++){
        for(int j = 1; j <= k; j++){
            int cur = INT_MAX;
            for(int n = 0; n <= j; n++){
                cur = min(cur, dp[(i - 1) % 2][j + 1 - n] + n * data[i - 1]);
            }
            dp[i % 2][j] = cur;
        }
    }
    return dp[n % 2][1];
}

//贪心 + 单调栈
vector<int> nextLower(const vector<int>& prices){
    int n = prices.size();
    vector<int> next_lower(n, n);
    stack<int> st;

    for(int i = n - 1; i >= 0; i--){
        while(!st.empty() && prices[st.top()] >= prices[i]){
            st.pop();
        }
        if(!st.empty()){
            next_lower[i] = st.top();
        }
        st.push(i);
    }
    return next_lower;
}
ll minCost(int n, int k, vector<int>& prices){
    vector<int> next_lower = nextLower(prices);
    ll total_cost = 0;
    int cur_carried = 0;
    for(int i = 0; i < n; i++){
        int days_to_cover = next_lower[i] - i;
        if(days_to_cover > k){
            days_to_cover = k;
        }
        int required = days_to_cover - cur_carried;
        if(required < 0) required = 0;
        if(required > 0){
            total_cost += (ll)required * prices[i];
            cur_carried += required;
        }
        cur_carried -= 1;
    }
    return total_cost;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    
    return 0;
}




//CF写法
void solve(){
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for(auto& num : nums){
        cin >> num;
    }
    vector<int> suf(n, n);
    stack<int> st;
    for(int i = n - 1; i >= 0; i--){
        while(!st.empty() && nums[st.top()] >= nums[i]){
            st.pop();
        }
        if(!st.empty()){
            suf[i] = st.top();
        }
        st.push(i);
    }
    for(auto& c : suf) cout  << c << ' ' << '\n';
    int sum = 0, carry = 0;
    for(int i = 0; i < n; i++){
        int dis = suf[i] - i;
        if(dis >= k){
            dis = k;
        }
        int need = dis - carry;
        if(need < 0){
            need = 0;
        }
        sum += need * nums[i];
        carry += need - 1;
    }
    cout << sum << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}


