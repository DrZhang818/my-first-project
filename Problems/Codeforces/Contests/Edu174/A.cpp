#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/contest/2069/problem/A
/*
    构造 
    题意:
        定义一个数组A的特征数组B: b2,b3,...,bn-1
        满足b[i] = (a[i] == a[i - 1] && a[i] == a[i + 1])
        现给出长度为n的数组A的特征数组B, 判断是否存在对应的数组A
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律
        由于每个数字的影响范围是三个数, 因此我们可以把问题转化成小规模问题
        一个数组B是合法的, 当且仅当B的任意长度为3的子数组均合法
        我们考虑枚举长度为3的8种情况
        000 001 010 011 100 101 110 111
        可以发现只有101这种情况是矛盾的, 因为两头的1要求中间必须和邻居相等, 但0又要求至少一个不相等
        因此我们枚举数组B, 看是否存在子数组101即可 
*/
void solve(){ 
    int n;
    cin >> n;
    n -= 2;
    vector<int> B(n);
    for(int i = 0; i < n; i++) {
        cin >> B[i];
    }
    bool ok = true;
    for(int i = 1; i < n - 1; i++) {
        if(B[i] == 0 && B[i - 1] == 1 && B[i + 1] == 1) {
            ok = false;
        }
    }
    if(ok) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
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
    
