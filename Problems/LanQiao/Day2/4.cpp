#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;
typedef pair<char,int> PCI;


//https://www.lanqiao.cn/problems/5323/learning/?contest_id=236
/*
    位运算 || 思维 || 分治思想
    题意:
        给定n个位运算操作和q次询问, 你需要回答每个询问按顺序经过操作后得到的数
        op: 由一个字符标示&|^ 以及一个数字num组成
    关键思考:
        一次位运算操作可以视为在各个数位上单独操作后再重新组合起来
        因此可以预处理1~30位(1e9)为0/1的结果, 最终处理询问只需要依次组合起来即可
    补充:
        位运算可以分为三类
        (1)不变
           ①&1 ②|0 ③^0
        (2)置0/1
           ①&0 ②|1
        (3)翻转
           ①^1
*/
void solve(){
    int n, q;
    cin >> n >> q;
    vector<PCI> a(n);

    for(int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
    }
    vector<int> d0(32), d1(32);
    for(int i = 0; i <= 30; i++){
        int c1 = 1 << i;
        int c0 = 0;
        for(auto &[c, num] : a){
            if(c == '&'){
                c0 &= num;
                c1 &= num;
            }else if(c == '|'){
                c0 |= num;
                c1 |= num;
            }else{
                c0 ^= num;
                c1 ^= num;
            }
        }
        d0[i] = (c0 >> i) & 1; 
        d1[i] = (c1 >> i) & 1; 
    }
    while(q--){
        int x, ans = 0;
        cin >> x;
        for(int i = 0; i <= 30; i++){
            if((x >> i) & 1 == 1){
                ans |= d1[i] << i;
            }else{
                ans |= d0[i] << i;
            }
        }
        cout << ans << "\n";
    }
}   
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}