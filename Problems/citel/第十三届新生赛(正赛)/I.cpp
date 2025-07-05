#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

/*
    字符串遍历 || 模拟
    题意: 给定一个小数, 要求求出精度(小数点后的位数-1)
        读入格式为a.b(a, b < 1e5)
        如0.001  1.00
    关键思考:
        正常用double存储是无法知道输入的精度的, 且读入数据告诉我们要使用字符串
        只需要计算小数点后的位数再-1即可
*/
void solve(){
    string s;
    cin >> s;
    int ans = 0;
    for(int i = 0, flag = 0; i < s.size(); i++){
        if(flag || s[i] == '.'){
            flag = true;
            ans++;
        }
    }
    cout << ans - 2 << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}