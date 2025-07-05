#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n;
    cin >> n;
    int size = 1 << n;
    vector<vector<ll>> grid(size, vector<ll>(size));
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cin >> grid[i][j];
        }
    }
    //dp[i][j][k] : 坐标(i, j) 为左上角的2^k * 2^k的矩形经过 k次脱发, 最少剩多少
    /*
        dp[i][j][k] = max(dp[s][t][k - 1]) / 2 + sum;
                    i or j + 2^k - 1 <= size - 1
                    i, j in range [0, size - 2^k]
                    s or t + 2^(k - 1) - 1 <= i or j + 2^k - 1
                    s, t in range [i or j, i or j + 2^(k - 1)]
        边界条件dp[i][j][0] = grid[i][j];

        sum怎么求: sum = sum[i + 2^k - 1][j + 2^k - 1] - sum[i - 1][j + 2 ^k - 1] - sum[i + 2^k - 1][j - 1] + sum[i - 1][j - 1]
                        -sum[s + 2^(k - 1) - 1][t + 2^(k - 1) - 1] - sum[s - 1][t + 2^(k - 1) - 1] - sum[s + 2^(k - 1) - 1][t - 1] + sum[s - 1][t - 1];
    */
    vector<vector<ll>> sum(size + 1, vector<ll>(size + 1, 0));
    for(int i = 1; i <= size; i++){
        for(int j = 1; j <= size; j++){
            sum[i][j] = grid[i - 1][j - 1] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }
    vector<vector<vector<db>>> dp(size, vector<vector<db>>(size, vector<db>(n + 1, 0)));
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            dp[i][j][0] = grid[i][j];
        }
    }
    for(int k = 1; k <= n; k++){
        const int POWK = 1 << k;
        const int POWLK = 1 << (k - 1);
        for(int i = 0; i <= size - POWK; i++){
            for(int j = 0; j <= size - POWK; j++){
                db curMax = 0;
                int maxs = 0, maxt = 0;
                db sumK = sum[i + POWK][j + POWK] - sum[i][j + POWK] - sum[i + POWK][j] + sum[i][j];
                db cur = LLONG_MAX;
                for(int s = i; s <= i + POWLK; s++){
                    for(int t = j; t <= j + POWLK; t++){
                        db sumLK = sum[s + POWLK][t + POWLK] - sum[s][t + POWLK] - sum[s + POWLK][t] + sum[s][t];
                        db TTsum = sumK - sumLK;
                        cur = min(cur, dp[s][t][k - 1] / 2 + TTsum);
                    }
                }
                dp[i][j][k] = cur;
            }
        }
    }
    
    /*
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cout << dp[i][j][1] << ' ';
        }
        cout << endl;
    }
    
    const int POWK = 1 << n;
    const int POWLK = 1 << (n - 1);
    db curMin = LLONG_MAX;
    db sumK = sum[POWK][POWK] - sum[0][POWK] - sum[POWK][0] + sum[0][0];
    //cout << "sumK :: " << sumK << endl;
    for(int s = 0; s <= POWLK; s++){
        for(int t = 0; t <= POWLK; t++){
            db sumLK = sum[s + POWLK][t + POWLK] - sum[s][t + POWLK] - sum[s + POWLK][t] + sum[s][t];
            //cout << s << ' ' << t << "::" << sumLK << endl;
            db TTsum = sumK - sumLK;
            curMin = min(curMin, dp[s][t][n - 1] / 2 + TTsum);
        }
    }
    */
    db curMin = floor(dp[0][0][n] * 10 + 0.5) / 10.0;
    printf("%.1lf\n", curMin);
   
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}




