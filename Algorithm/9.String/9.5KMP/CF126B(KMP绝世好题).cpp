#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://codeforces.com/problemset/problem/126/B
/*
    DP || 思维
    题意:
        给定一个长度为n的字符串s, 找出s中的一个最长的合法子串t:
        满足t既是s的前缀, 也是s的后缀, 同时也是s的中间组成部分(非前缀且非后缀)
        无解输出"Just a legend"
        范围: n∈[1,1e6]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质, t既是s的前缀又是s的后缀, 这让我们自然想到构建lps数组
        lps[i] := s[0:i-1]与s[1:i]的最长公共前后缀(真包含)
        想到这一点后, 我们就可以把问题转化为: 
            在s的所有公共前后缀中, 找出在中间部分出现过的最长的一个
        对于第一个操作, 寻找s的所有公共前后缀是很简单的, 只需利用lps数组进行跳跃即可
        难点在于如何高效判断是否在中间出现过
        首先证明一个简单的引理: 
        (1)如果长度为len的前缀在中间出现过, 长度<=len的前缀在中间都出现过
        由引理(1)不难得到以下推论
        (2)如果长度>=len的前缀在中间出现过, 那么长度为len的前缀也在中间出现过
        下面证明引理(1)
            假设前缀s[0:i]==s[u:v], u > 0 && v < n - 1
            对于0 <= j <= i, 我们令w = v - (i - j) = v - i + j
            显然有s[0:j]==s[u:v-i+j], 否则与s[0:i]==s[u:v]矛盾
        本题实际要使用的是推论(2)
        我们可以利用已经求出来的lps数组, 寻找前缀与中间部分的最长匹配长度mx
        这样对于s的一个公共前后缀t, 我们只需要判断len(t)是否小于等于mx
        如果成立的话, 由推论(2)我们立即可以知道, 长度为len(t)的前缀在中间出现过
        这样我们从lps[n]往下跳, 找到的第一个满足条件的就是所求的最长串
*/
void solve() { 
    string s;
    cin >> s;
    int n = s.size();
    vector<int> lps(n + 1);
    for(int i = 1; i < n; i++) {
        int j = lps[i];
        while(j && s[i] != s[j]) j = lps[j];
        lps[i + 1] = s[i] == s[j] ? j + 1 : 0;
    }
    int mx = 0;
    for(int i = 2; i <= n - 1; i++) mx = max(mx, lps[i]);
    int cur = lps[n];
    while(cur > 0) {
        if(cur <= mx) {
            cout << s.substr(0, cur) << "\n";
            return ;
        }
        cur = lps[cur];
    }
    cout << "Just a legend\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
