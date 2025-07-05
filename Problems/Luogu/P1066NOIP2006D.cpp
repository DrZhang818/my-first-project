#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
//https://www.luogu.com.cn/problem/P1066
//目标: 计算满足二进制位数限制w的2^k进制数r, 其中r至少为两位且每一位严格递增, 求r的数量

//字符串加法
string add_strings(const string& a, const string& b){
    string res;
    int carry = 0, i = a.size() - 1, j = b.size() - 1;
    while(i >= 0 || j >= 0 || carry){
        int sum = carry;
        if(i >= 0) sum += a[i--] - '0';
        if(j >= 0) sum += b[j--] - '0';
        carry = sum / 10;
        res += (sum % 10) + '0';
    }
    reverse(res.begin(), res.end());
    return res;
}

void solve(){
    int k, w;
    cin >> k >> w;
    int b = 1 << k;
    //预处理组合数
    int MAX_N = b - 1;//既是位数上界，也是每一位的取值上界
    vector<vector<string>> C(MAX_N + 1,  vector<string>(MAX_N + 1, "0"));
    C[0][0] = "1";
    for(int n = 1; n <= MAX_N; n++){
        C[n][0] = "1";
        C[n][n] = "1";
        for(int m = 1; m < n; m++){
            C[n][m] = add_strings(C[n - 1][m], C[n - 1][m - 1]);
        }
    }
    //计算r的最大位数(例如k = 3, w = 7, 根据7 = 1 + 3 + 3, 最大位数为3，即ceil(7 / 3))
    int m_max = (w + k - 1) / k;//避免浮点数
    m_max = min(m_max, MAX_N);//由于有递增特性, 最大位数为2^k - 1, 如k = 3, 最大为1234567

    /*
        计算位数为m_max的数r的最高位的取值范围
        例如k = 3, w = 7
        m_max = 3, 即计算位数为3的r的最高位的取值范围
        123 124 ... 127
            134 ... 137
                ...
                    167
        ...............
        D ... 7

        即最高位可以取[1, D]
    */
    int w_mod_k = w % k;
    int D = w_mod_k == 0 ? MAX_N : (1 << w_mod_k) - 1;
    /*
    if(w_mod_k == 0){        例如k = 3, w = 6, 最高位范围是[1, 7], 因为转化后保证位数在k = 3以内
        D = (1 << k) - 1;
    }
    else{
        D = (1 << w_mod_k) - 1;
    }
    */

    string total_sum = "0";

    /*
        计算位数为[2, m_max)的r
        对于每一个m, 它的每一位取值都在[1, MAX_N]内
        相当于从MAX_N个数中挑出m个, 并按递增排列
        由于递增性, 排列方式唯一
        因此方案数就等于组合数C[MAX_N][m]
    */
    for(int m = 2; m < m_max; m++){
        total_sum = add_strings(total_sum, C[MAX_N][m]);
    }


    /*
        计算位数为m_max的r
        此时最高位的取值为[1, D]
            其余位的取值为[D + 1, MAX_N]
        对于最高位的每一个取值d1
            方案数相当于从MAX_N - (D + 1) + 1 == MAX_N - D中挑选m_max - 1个数
        因此方案数就等于组合数C[MAX_N - D][m_max - 1]
        注意： 当m_max - 1 > MAX_N - D时, 方案数为0(不合法)
    */
    if(m_max >= 2 && m_max <= b){
        for(int d1 = 1; d1 <= D; d1++){
            int remaining = MAX_N - d1;//剩余可选的数量
            if((m_max - 1) > remaining) continue;
            total_sum = add_strings(total_sum, C[remaining][m_max - 1]);
        }
    }

    cout << total_sum << endl;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}