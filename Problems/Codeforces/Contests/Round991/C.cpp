#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/2050/problem/C
/*
    数学 || 暴力枚举 || 动态规划(状压DP)
    题意: 给定长度为n的数字字符串, 判断能否经过下列操作使得数字被9整除
        op1: 把数字2变为4
        op2: 把数字3变为9
    关键性质:
        一个数能被9整除, 当且仅当该数字的数位和被9整除
        记录数字和在模9空间中为x
        则每次操作相当于把x变为(x + delta) % 9, 其中delta属于{2, 6}
        记录op1的次数为cnt2, op2的操作为cnt3
        问题转化为是否存在合法p, q 使得(x + p * 2 + q * 6) % 9 == 0
            一个p, q是合法的, 如果0 <= p <= cnt2  0 <= q <= cnt3
        进一步的:
            (x + p * 2 + q * 6) % 9 = (x % 9 + (p * 2) % 9 + (q * 6) % 9) % 9
            于是p的上界可取min(8, cnt2)
                q的上界可取min(2, cnt3)
    到此, 问题彻底转化为一个二重循环枚举的问题, 由于枚举次数为常数, 时间可接受
*/

//1.暴力枚举
void solve1(){
    string s;
    cin >> s;
    int x = 0, cnt2 = 0, cnt3 = 0;
    for(int i = 0; i < s.length(); i++){
        x = (x + s[i] - '0') % 9;
        cnt2 += s[i] == '2';
        cnt3 += s[i] == '3';
    }   
    bool ok = false;
    for(int i = 0; i <= cnt2 && i < 9; i++){
        for(int j = 0; j <= cnt3 && j < 3; j++){
            if((x + i * 2 + j * 6) % 9 == 0){
                ok = true;
                break;
            }
        }
        if(ok) break;
    }
    if(ok){
        cout << "YES\n";
    }else{
        cout << "NO\n";
    }
}
//2.jiangly的状压DP
void solve2(){
    string n;
    cin >> n;

    int f = 1;
    for(auto c : n){
        int d = c - '0';
        int x = d * d;
        int nf = f << d;
        if(x < 10){
            nf |= f << x;
        }
        nf |= nf >> 9;
        nf &= (1 << 9) - 1;
        f = nf;
    }
    if(f & 1){
        cout << "YES\n";
    }else{
        cout << "NO\n";
    }
}
//比赛时做法
void solve3(){
    string s;
    cin >> s;
    int sum = 0, cnt2 = 0, cnt3 = 0;
    for(auto &c : s){
        if(c == '2'){
            cnt2++;
        }
        if(c == '3'){
            cnt3++;
        }
        sum += c - '0';
    }
    vector<bool> nums(19);
    for(int i = 0; i <= 18 && i <= 2 * cnt2; i += 2){
        nums[i] = true;
        for(int j = 0; j <= min(3, cnt3); j++){
            if(i + 6 * j <= 18){
                nums[i + 6 * j] = true;
            }
        }
    }
    int mod = sum % 9;
    for(int i = 0; i <= 18; i++){
        if(nums[i]){
            if((mod + i) % 9 == 0){
                cout << "YES\n";
                return;
            }
        }
    }
    cout <<"NO\n";
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