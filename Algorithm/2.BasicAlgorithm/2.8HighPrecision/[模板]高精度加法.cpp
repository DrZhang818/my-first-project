#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://www.luogu.com.cn/problem/P1601
/*
    模拟 || 高精度
    题意:
        给定两个非负整数a,b, 计算a + b的值
        范围: a,b∈[0, 1e500]
    关键思考:
        本题是模拟类题目, 常用思考方式为: 明确题目要维护的信息, 选择合适的数据结构按题意执行
        由于超出了ll的表示范围, 我们需要利用模拟加法来实现信息维护
        模拟的关键在于如何存储、如何传递进位信息
        存储时可以使用vector也可以使用string, 注意要倒序存储, 因为要从个位开始计算
        传递进位信息时我们可以用一个变量t存储计算值
        计算到第i位时, 令t += A[i] + B[i]
        此时t包含了i - 1位的进位信息, 又加上了A[i]和B[i]的值
        此时第i位的值就应该是t % 10
        再把t /= 10之后, 就变成了第i位向第i + 1位传递的进位信息
        最后, 判断最高位是否有进位信息, 如果有就需要将lc加1, 并把最高位置为t
*/
void solve() { 
    string a, b;
    cin >> a >> b;
    int la = a.size(), lb = b.size(), lc = max(la, lb);
    vector<int> A(100005), B(100005), C(100005);
    for(int i = la - 1; i >= 0; i--) {
        A[la - 1 - i] = a[i] - '0';
    }
    for(int i = lb - 1; i >= 0; i--) {
        B[lb - 1 - i] = b[i] - '0';
    }
    auto add = [&]() -> void {
        int t = 0;
        for(int i = 0; i < lc; i++) {
            t += A[i] + B[i];
            C[i] = t % 10;
            t /= 10;
        }
        if(t) {
            C[lc++] = t;
        }
    };
    add();
    for(int i = lc - 1; i >= 0; i--) {
        cout << C[i];
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
