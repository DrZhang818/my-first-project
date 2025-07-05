#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://codeforces.com/contest/1857/problem/C
/*
    构造
    题意:
        给定一个正整数N和一个长度为N(N-1)/2的数组B, B的生成过程为:
        有一个长度为N的数组A, 对所有满足i < j的下标对, 将min(a[i],a[j])添加到B中
        生成后, B数组的顺序全部打乱, 要求构造出一个合法的A能够生成B
        范围: n∈[2,1e3], Ai,Bi∈[-1e9,1e9]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        经典的贡献法, 我们可以从A数组角度来思考
        将A数组排好序后, 如[1,2,3,4]
        我们发现1的贡献为3, 2的贡献为2, 3的贡献为1, 4的贡献为0
        这里说的贡献是在B数组中贡献的长度(次数), 这个规律可以用握手定理解释
        因此, 我们反过来看B数组
        将B数组排好序后[1,1,1,2,2,3]
        前3个应该为一组, 接着2个为一组, 接着1个为一组, ...
        于是构造方法就是把B数组排序, 依次按照长度为n-1 -> 1进行分组即可构造出A
        A的最后一个元素取倒数第二个即可
*/
void solve() { 
    int n;
    cin >> n;
    int len = n * (n - 1) / 2;
    vector<int> a(len + 1);
    for(int i = 1; i <= len; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    int j = 1;
    for(int i = n - 1; i >= 1; i--) {
        cout << a[j] << " ";
        j += i;
    }
    cout << a.back() << "\n";
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
    
