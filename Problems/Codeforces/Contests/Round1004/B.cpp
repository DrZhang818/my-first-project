#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/contest/2067/problem/B
/*
    贪心 || 构造
    题意:
        给定两个袋子, 第一个袋子里有n个数字,而第二个袋子是空的, 你可以进行以下操作：
        op1: 从第一个袋子中选择任意一个数字，并将其移动到第二个袋子中。
        op2: 从第一个袋子中选择一个"第二个袋子中也有的"数字，并将该数加1。
        这两种操作的次数不限, 顺序不限
        判断能否使第一个和第二个袋子中的数字完全相同
        范围: n∈[2,1000], ai∈[1,n], t∈[1,1e4], 保证n²<=1e6
    关键思考:
        本题的一个重要信息是"并将该数加1", 这意味着我们无法获得最小的数
        于是很自然的想法就是从小到大进行贪心, 判断当前最小的数是否合法
        (1)如果最小的数只有一个, 那么显然不合法
        (2)如果最小的数有 >= 2个, 我们希望能够把最小的数向大数进行转化, 以使后面的"最小数"数量尽量不为1
        假设当前有k个x, 我们可以把1个放在上面, 1个放在下面, 其余k-2个都可以转化成x + 1
        因此最优策略就是让x + 1的次数加上k - 2
        如果发现某个数次数为0, 代表两个袋子都没有, 自然是合法的
        如果某个数次数为1, 此时前面所有比他小的数都已经配对成功, 那么就没有数可以转成当前数了, 因此不合法
        枚举时需要估计上下界
        下界自然是1
        上界: 考虑n个n, 配对成功后上下都有n / 2个(n + n / 2)
        因此上界是(n + n / 2);
*/
void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    unordered_map<int,int> mp;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        mp[a[i]]++;
    }
    for(int i = 1; i <= n + (n / 2); i++) {
        if(mp[i] == 0) continue;
        if(mp[i] == 1) {
            cout << "No\n";
            return;     
        }
        mp[i + 1] += mp[i] - 2;
    }
    cout << "Yes\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}

