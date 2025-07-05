#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

const int MOD = 19260817;

//https://citel.bjtu.edu.cn/acm/problem/1957

/*
    矩阵快速幂优化DP(概率期望DP) || 数学算法: 概率期望(马尔科夫链)
    1.状态定义:
        由于分数的变化依赖于连续的胜利场次，我们可以将问题建模为一个马尔可夫链。
        定义不同的状态来表示当前的连续胜利场次：
        状态0：当前没有连续胜利（上局为失败）。
        状态1：当前有1次连续胜利。
        状态2：当前有2次连续胜利。
        状态3：当前有3次或以上连续胜利。
    2.状态转移:
        根据当前状态和游戏结果（胜利或失败），定义状态转移矩阵：
        从状态0：
            胜利转移到状态1，得分增加1分。
            失败保持在状态0，得分减少1分。

        从状态1：
            胜利转移到状态2，得分增加1分。
            失败转移到状态0，得分减少1分。

        从状态2：
            胜利转移到状态3，得分增加1分并获得奖励1分（共增加2分）。
            失败转移到状态0，得分减少1分。

        从状态3：
            胜利保持在状态3，得分增加1分并获得奖励1分（共增加2分）。
            失败转移到状态0，得分减少1分。
            
    设E[i]为当前处于状态𝑖时，剩余游戏局数为𝑘的期望分数增量。
    E[i][k] = p × (得分增加 + E[下一状态][k−1]) + q × (得分减少 + E[状态0][k−1])
*/
ll fast_mi(ll a, ll b){
    ll res = 1;
    a %= MOD;
    if(a < 0) a += MOD;
    while(b > 0){
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res; 
}

vector<vector<ll>> mat_mult(vector<vector<ll>> &A, vector<vector<ll>> &B){
    int size = A.size();
    vector<vector<ll>> C(size, vector<ll>(size, 0));
    for(int i = 0; i < size; i++){
        for(int k = 0; k < size; k++){
            for(int j = 0; j < size; j++){
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

vector<vector<ll>> mat_pow(vector<vector<ll>> &A, ll power){
    int size = A.size();
    vector<vector<ll>> res(size, vector<ll>(size, 0));
    for(int i = 0; i < size; i++) res[i][i] = 1;
    while(power > 0){
        if(power & 1) res = mat_mult(res, A);
        A = mat_mult(A, A);
        power >>= 1;
    }
    return res;
}
void solve(){
    ll n, a, b;
    cin >> n >> a >> b;
    ll inv_b = fast_mi(b, MOD - 2);
    ll yes = a * inv_b % MOD;
    ll no = (1 - yes + MOD) % MOD;

    vector<vector<ll>> T(5, vector<ll>(5, 0));
    T[0][0] = no;
    T[0][1] = yes;
    T[0][4] = (no * (MOD - 1) + yes) % MOD; // 常数项 -1 * no + 1 * yes

    T[1][0] = no;
    T[1][2] = yes;
    T[1][4] = (no * (MOD - 1) + yes) % MOD;

    T[2][0] = no;
    T[2][3] = yes;
    T[2][4] = (no * (MOD - 1) + yes * 2) % MOD;

    T[3][0] = no;
    T[3][3] = yes;
    T[3][4] = (no * (MOD - 1) + yes * 2) % MOD;

    T[4][4] = 1;

    vector<vector<ll>> Tn = mat_pow(T, n);
    ll ans = Tn[0][4];
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int k;
    cin >> k;
    while(k--){
        solve();
    }
    return 0;
}