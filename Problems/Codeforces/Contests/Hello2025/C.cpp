#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/2057/problem/C
/*
    构造 || 贪心思维 || 位运算
    题意:
        给定两个整数L和R, 要求在[L,R]范围内找到一个三元组(a,b,c)
        满足(a^b) + (b^c) + (a^c)为所有三元组组合中的最大值
    关键思考:
        首先考虑怎么构造两个数的最大异或值?
            R: 1110010101
            L: 1110000111
               0000011111
        贪心的想, 让异或值最大等价于满足以下两个性质:
        (1)两个二进制数尽量多的位置不同(能组成1就组成1)
        (2)构造出的数必须在[L,R]内
            即只能把R中1的位置改为0, 把L中0的位置改成1
        结合起来看, 其实就是求(L^R)的最高位1, 这是第一个可以组成1的位置
        之后构造的数就是.....10000和.....01111
        对于以上例子, 我们要找到1111的二进制表示, 这就是t = (1<<__lg(R^L))-1
        那么a = R & ~t, b = a - 1
        以上写法可以用位运算实现, 也可用循环实现

        那么第三个数c怎么构造呢? 
        还是拿这个例子:
            R: 1110010101
            L: 1110000111
        我们发现c的活动范围只会影响后五位(这还是由(L^R)的最高位决定的)
        而我们得到的a^b在后五位全部是1, 这意味着
        (a^c) + (b^c)必然是定值, 因为当(a^c)在第i位为1时, (b^c)在这一位必然相同
        那么c的取值就是[L,R]内任意一个数即可了
        以上构造是否是最优的呢?
        证明: 
            我们假设a,b,c三个数可以取等
            那么在a^b是最优的情况下, c取a或者取b一定是最优的, 这样得到的答案是2 * (a^b)
            而由上面的讨论可知, c在[L,R]内无论取何值, 最后结果都是定值, 且a,b∈[L,R]
            因此, c取任意值得到的都是最大值2*(a^b), 答案是最优的
            证毕
        从而本题转化为构造a^b最大的问题
*/
//优化做法1
void solve1(){
    int l, r;
    cin >> l >> r;
    int t = (1 << __lg(r ^ l)) - 1;
    int a = r & ~t, b = a - 1, c = l;
    while(c == a || c == b) c++;
    cout << a << " " << b << " " << c << "\n"; 
}
//优化做法2(jiangly)
void solve2(){
    int L, R;
    cin >> L >> R;
    int a = 0, b = 0, c = 0;
    for(int i = 29; i >= 0; i--){
        if((L ^ R) >> i & 1){
            b |= 1 << i;
            a |= (1 << i) - 1;
            break;
        }
        else{
            a |= L & (1 << i);
            b |= L & (1 << i);
        }
    }
    c = L;
    while(c == a || c == b){
        c++;
    }
    cout << a << " " << b << " " << c << "\n";
}
void solve(){
    int l, r;
    cin >> l >> r;
    int t = (l^r), lenl = __lg(l), lent = __lg(t), lenr = __lg(r);
    if(lenl == lenr){
        int a = (r & (~((1 << lent)-1)));
        cout << a << " " << a - 1 << " " << (r == a ? l : r) << "\n";
    }else{
        int a = 1 << lenr;
        cout << a << " " << a - 1 << " " << (r == a ? l : r) << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve2();
    }
    return 0;
}
