#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

//https://leetcode.cn/problems/smallest-number-with-all-set-bits/
/*
    位运算
    例如 5 :   0101
        答案是 0111
    相当于求n的位掩码
    核心就是求解二进制长度
*/

// 第一种写法
class Solution {
public:
    int smallestNumber(int n) {
        return (1 << (__lg(n) + 1)) - 1;
    }
};

// 第二种写法
class Solution{
public:
    int smallestNumber2(int n){
        return (1 << bit_width((unsigned) n)) - 1;
    }
};
int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    return 0;
}