#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/problemset/problem/1365/C
/*
    题意:
        给你一个正整数n和两个1~n的排列a, b，你可以对排列进行任意次旋转
        求出两个排列对应位置相等的最大个数
    关键思考:
        本题思考时错误地往KMP方向进行思考, 这样的问题在于:
        KMP本质是一种滑动窗口, 是处理子数组匹配问题
        而本题不要求是连续地相等, 属于子序列问题
        正确的思考为:
        (1)旋转顺序不妨设为逆时针
        (2)不妨只对数组b进行操作
        在以上前提下, 我们有两种方式:
        1.求出让1~n分别对齐时需要的旋转次数, 这样如果两个数的次数相等
          那么在旋转相应次数后, 两个数必然对齐
          实现方式是做一个映射, 把元素x映射为在数组中出现的位置
        2.求出b[i]对齐a[i]需要的旋转次数
          实现方式是对数组a先做一个 值->位置的映射       
          然后把数组b的每个值经过ai[]进行映射
          现在我们知道b[i]在a中应该出现的位置是b'[i]
          而b[i]当前的实际位置是i
          所以需要调整(b'[i] - i + n) % n次
*/
//写法一: 按元素0~n逐个对齐
void solve1(){
    int n;
    cin >> n;
    vector<int> a(n), b(n), ai(n), bi(n), c(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        ai[a[i] - 1] = i;
    }
    for(int i = 0; i < n; i++){
        cin >> b[i];
        bi[b[i] - 1] = i;
    }
    for(int i = 0; i < n; i++){
        c[(ai[i] - bi[i] + n) % n]++;
    }
    cout << *max_element(c.begin(), c.end()) << "\n";
}
//写法二: 按b[i]在a中的出现位置计算偏移
void solve2(){
    int n;
    cin >> n;
    vector<int> a(n), b(n), ai(n), c(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        ai[a[i] - 1] = i;
    }
    for(int i = 0; i < n; i++){
        cin >> b[i];
        b[i] = ai[b[i] - 1];
        c[(b[i] - i + n) % n]++;
    }
    cout << *max_element(c.begin(), c.end()) << "\n";
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve2();
    return 0;    
}
