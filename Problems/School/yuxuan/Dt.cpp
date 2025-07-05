#include <bits/stdc++.h>
using namespace std;
 
// 新的辅助数组 H：若 n<10, H(n)=0；否则 H(n)= digitSum(n) + H(digitSum(n))
long long H[205];
 
// 计算一个数的各位数字和
int digitSum(int n) {
    int s = 0;
    while(n > 0){
        s += n % 10;
        n /= n;
    }
    return s;
}
 
// 预处理 H 数组（n 从 0 到 maxN）
void precomputeH(int maxN) {
    for (int i = 0; i <= maxN; i++){
        if(i < 10) H[i] = 0;
        else {
            int s = digitSum(i);
            H[i] = s + H[s];
        }
    }
}
 
// 我们需要计算 S(x)=∑_{j=1}^{x} T(j)
// T(j)= 0, 如果 j 为单个数字；
// T(j)= f_1(j)+f_1(f_1(j))+... = (digitSum(j) + H(digitSum(j))) 如果 j 为多位数.
 
string digits;
int nDigits;
 
// DP 返回一个 Pair {count, total}：
// count 表示当前分支构造出的数的个数；
// total 表示这些数的 T(j) 贡献总和.
struct Pair {
    long long cnt;
    long long sum;
};
 
// DP 状态
struct State {
    int pos, cnt, sum, tight, started;
    bool operator==(const State &other) const {
        return pos == other.pos && cnt == other.cnt && sum == other.sum && tight == other.tight && started == other.started;
    }
};
 
struct StateHash {
    std::size_t operator()(const State &s) const {
        int h = s.pos;
        h = h * 31 + s.cnt;
        h = h * 31 + s.sum;
        h = h * 31 + s.tight;
        h = h * 31 + s.started;
        return h;
    }
};
 
unordered_map<State, Pair, StateHash> memo;
 
// DP 函数：在当前状态下返回 {数量, T(j) 贡献总和}
Pair dp(int pos, int cnt, int curSum, int tight, int started) {
    if(pos == nDigits) {
        if(!started) return {0, 0}; // 排除数字 0
        // 如果只有一位，则 j 是单数字，贡献为 0；否则贡献为 digitSum(j) + H(digitSum(j))
        if(cnt < 2) return {1, 0};
        else return {1, curSum + H[curSum]};
    }
    State st{pos, cnt, curSum, tight, started};
    if(memo.find(st) != memo.end())
        return memo[st];
    Pair res = {0, 0};
    int limit = tight ? (digits[pos] - '0') : 9;
    for(int d = 0; d <= limit; d++){
        int ntight = tight;
        if(tight && d < limit) ntight = 0;
        int nstarted = started;
        int ncnt = cnt;
        int nsum = curSum;
        if(!started && d > 0) {
            nstarted = 1;
            ncnt = 1;
            nsum = d;
        } else if(started) {
            ncnt = cnt + 1;
            nsum = curSum + d;
        }
        Pair sub = dp(pos + 1, ncnt, nsum, ntight, nstarted);
        res.cnt += sub.cnt;
        res.sum += sub.sum;
    }
    memo[st] = res;
    return res;
}
 
// 计算 S(x)=∑_{j=1}^{x} T(j)
long long computeS(long long x) {
    digits = to_string(x);
    nDigits = digits.size();
    memo.clear();
    Pair ans = dp(0, 0, 0, 1, 0);
    return ans.sum;
}
 
// 利用二分查找找到满足 S(x)= s 的最小 x（题目保证 x 存在）
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    precomputeH(200); // 预处理 H 数组
    
    int t;
    cin >> t;
    while(t--){
        long long s;
        cin >> s;
        long long lo = 1, hi = s + 10, ans = -1;
        while(lo <= hi){
            long long mid = (lo + hi) / 2;
            long long val = computeS(mid);
            if(val == s){
                ans = mid;
                hi = mid - 1; // 找更小的 x
            } else if(val < s) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
