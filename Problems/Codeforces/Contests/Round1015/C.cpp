#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
//https://codeforces.com/contest/2084/problem/C
/*
    构造 || 贪心 || 模拟
    题意:
        给定两个长度为n的排列a,b, 你最多可以进行n次操作:
        op: 选择两个不同下标i,j, 交换a[i]和a[j], b[i]和b[j]
        判断能否在操作后使得a,b互为逆序, 即对任意i∈[1,n], 有a[i] = b[n - i + 1]
        如果有解, 输出操作次数以及操作方案; 如果无解, 输出-1
        范围: n∈[2,2e5]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        首先观察题目性质, 容易发现: 有解的必要条件是若存在<x,y>, 则存在<y,x>
        深入思考发现, 解的存在情况还与奇偶性有关
        当n为奇数时, 有且仅有一个二元组允许y = x, 即有且仅有一个二元组<x,x>
        当n为偶数时, 不允许任何一个二元组满足y = x
        因此我们推出了有解的必要条件, 可以据此写出判断无解的条件
        代码实现时, 使用vis数组建边, 判断是否存在矛盾
        接下来思考如何构造合法解
        首先特判奇数情况, 先把<x,x>放在n / 2 + 1的位置, 然后奇数和偶数就可以一起写了
        接着就是从左向右贪心操作的过程, 只要发现不匹配的数对, 就进行操作
        这样保证每次操作都能把[l,r]的问题转化成[l+1,r-1]的问题
        那最终至多操作n / 2次即可构造出合法方案
        具体操作就是使用map存储<x,y>的逆序<y,x>的索引位置
        即通过<x,y>找到它的逆序所在位置
        然后从左到右模拟即可, 每当发现逆序位置不是n - i + 1, 就进行swap操作
        注意调整后要把原本的mp[{b[n - i + 1], a[n - i + 1]}] 更新为pos
*/
void solve() { 
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    vector<int> vis(n + 1, 0);
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] == b[i]) cnt++;
        if(vis[a[i]] && b[i] != vis[a[i]] || vis[b[i]] && a[i] != vis[b[i]]) {
            cout << -1 << "\n";
            return;
        }
        vis[a[i]] = b[i];
        vis[b[i]] = a[i];
    }
    if(cnt > (n & 1)) {
        cout << -1 << "\n";
        return;
    } 
    vector<PII> ans;
    if(n % 2 == 1) {
        for(int i = 1; i <= n; i++) {
            if(a[i] == b[i] && i != n / 2 + 1) {
                ans.push_back({i, n / 2 + 1});
                swap(a[n / 2 + 1], a[i]);
                swap(b[n / 2 + 1], b[i]);
                break;
            }
        }
    }
    map<PII, int> mp;
    for(int i = 1; i <= n; i++) {
        mp[{b[i], a[i]}] = i;
    }
    for(int i = 1; i <= n / 2; i++) {
        int pos = mp[{a[i], b[i]}];
        if(pos != n - i + 1) {
            ans.push_back({pos, n - i + 1});
            mp[{b[n - i + 1], a[n - i + 1]}] = pos;
            swap(a[pos], a[n - i + 1]);
            swap(b[pos], b[n - i + 1]);
        }
    }
    cout << (int)ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i].first << " " << ans[i].second << "\n";
    }
    // for(int i = 1; i <= n; i++) {
    //     cout << a[i] << " \n"[i == n];
    // }
    // for(int i = 1; i <= n; i++) {
    //     cout << b[i] << " \n"[i == n];
    // }
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
    
