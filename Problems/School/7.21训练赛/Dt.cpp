#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
const ull P = 13131;

//https://www.luogu.com.cn/problem/P6273
/*
    前缀和 || 数学 || 思维
    题意:
        给定一个长度为N的字符串, 设S中不同的字符数为k
        一个子串是合法的, 当且仅当该子串中不同的字符数为k, 且每个字符的出现次数都相同
        请你求出S中有多少个合法子串, 答案对1000000007取模
        范围: N∈[2,1e5], 字符集∑为[a,z]∪[A,Z]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        首先思考暴力方法, 我们枚举所有k的整数倍的定长滑窗, 用multiset维护字符最小次数和最大次数
        时间复杂度为O(n^2/k * logn)
        优化的关键在于如何快速判断"每个字符出现次数相同"这件事
        设s的字符集为T
        对于子串s[l:r], 我们钦定T中任意一个字符为标准字符, 记其出现次数为cnt
        那么T中的每个字符的出现次数都应该是cnt
        我们对每个字符统计前缀和
        pre[i][ch] := 子串s[1:i]中字符ch的出现次数
        那么有all(pre[r][ch] - pre[l-1][ch] = cnt for ch in T)
        不妨设标准字符为x
        那么就是 pre[r][ch] - pre[l - 1][ch] = pre[r][x] - pre[l - 1][x]
        移项得, pre[r][ch] - pre[r][x] = pre[l - 1][ch] - pre[l - 1][x]
        每个字符ch都形成一个状态: pre[i][ch] - pre[i][ch]
        这样把T中所有字符的状态都压缩在一起, 就得到了第i个位置的状态
        后续枚举j时, 只需要看看前面有多少个i与其状态完全相同即可
        压缩状态可以采用字符串哈希的方式
*/
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = "#" + s;
    vector<map<char,int>> mp(n + 1);
    map<char,bool> vis;
    char ch = s[1];
    for(int i = 1; i <= n; i++) {
        mp[i][s[i]]++; 
        vis[s[i]] = true;
        for(char j = 'a'; j <= 'z'; j++) {
            mp[i][j] += mp[i - 1][j];
        }
        for(char j = 'A'; j <= 'Z'; j++) {
            mp[i][j] += mp[i - 1][j];
        }
    }
    int ans = 0;
    unordered_map<ull,int> cnt;
    cnt[0] = 1;
    for(int i = 1; i <= n; i++) {
        int cnt_x = mp[i][ch];
        ull H = 0;
        for(auto [cur, c] : mp[i]) {
            if(vis[cur]) {
                H = H * P + c - cnt_x;
            }
        }
        add(ans, cnt[H]);
        cnt[H]++;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
