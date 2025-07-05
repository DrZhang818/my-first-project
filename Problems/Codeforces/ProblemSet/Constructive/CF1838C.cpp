#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
//https://codeforces.com/problemset/problem/1838/C
/*
    构造 || 数论
    题意:
        给定一个N × M的矩阵, 要求把排列P: 1~N*M填入矩阵, 使得矩阵合法
        一个矩阵是合法的, 当且仅当任意两个相邻格的绝对差都不是质数
        范围: n,m∈[4,1000]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据出发探寻规律, 从特殊到一般
        首先思考很容易发现只要n和m有一个为偶数, 我们就能直接按顺序填写来构造出来了
        这里利用到以下两个性质
        (1)相邻的两个自然数之差为1, 1不是质数
        (2)除了2之外的所有偶数都不是质数
        考虑到二维矩阵的编号为 i * m + j || j * n + i
        当n或m有一个为偶数时, 我们就沿着相应的方向进行填写, 保证差值为一个大于2的偶数
        这样就解决了所有n * m % 2 == 0的情况

        当n和m都是奇数的时候, 上述构造方法就不一定成立了
        但我们换个角度想, 只要下一行整体向左做一次轮换
        1 2 3 4 5   ---- 1 2 3 4  5
        6 7 8 9 10  ---- 7 8 9 10 6
        这样一是保证了前四个都是偶数, 二是保证了最后一个差值为1
        又完美符合性质(1)(2)
        以下每行都依次做1, 2, ..., k次轮换, 就可以得到合法解了
*/
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    if(n * m % 2 == 0) {
        if(n % 2 == 0) {
            for(int j = 0; j < m; j++) {
                for(int i = 0; i < n; i++) {
                    a[i][j] = n * j + i + 1;
                }
            } 
        } else {
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    a[i][j] = m * i + j + 1;
                }
            }
        }
    } else {
        int idx = 1;
        for(int i = 0; i < n; i++) {
            int j = ((m - i) % m + m) % m;
            for(int c = 0; c < m; c++, j = (j + 1) % m) {
                a[i][j] = idx++;
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << a[i][j] << " \n"[j == m - 1];
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
