#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://atcoder.jp/contests/dp/tasks/dp_c
/*
    网格图DP
    注意本题状态转移来自左侧或右侧，因此不可用一维滚动数组
*/
void solve(){
    int n;
    cin >> n;
    vector<vector<int>> grid(n, vector<int>(3));    
    for(auto& r : grid) for(auto& c : r) cin >> c;
    vector<vector<int>> dp(2, vector<int>(5));
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= 3; j++){
            for(int k = 1; k <= 3; k++){
                if(k == j) continue;
                dp[i % 2][j] = max(dp[i % 2][j], dp[(i - 1) % 2][k] + grid[i - 1][k - 1]);            
            }
        }
    }   
    cout << *max_element(dp[n % 2].begin(), dp[n % 2].end()); 
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}