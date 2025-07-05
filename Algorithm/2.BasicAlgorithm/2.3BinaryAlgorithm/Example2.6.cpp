#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


/*
    最优划分问题
    二分 || 贪心
    题意:
        给定一个长度为n的数组, 要求将其划分为3个非空子数组
        使得每个子序列的和的最大值最小, 求出这个值
    关键思考:
        最大值最小化是很经典的二分答案模型, 只要我们发现答案具有某种单调性
        就可以利用二分答案来优化时间复杂度
        对于本题, 我们可以在[mx, sum]范围内进行二分查找
        假设x可以满足存在一种合法划分, 满足三个数组的最大值≤x
        那么x + 1, x + 2, ...一定都可以满足
        这就是二分答案所必须具备的单调性
        接着就是利用贪心算法写出check函数即可
        即从左到右贪, 分成三个桶, 每个桶尽可能多地装下前面的数, 这样一定是最优划分
*/
void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    int sum = 0, mx = INT_MIN;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
        mx = max(mx, a[i]);
    }
    auto check = [&](int x) -> bool {
        int cnt = 0, curS = 0;
        for(int i = 0; i < n; i++) {
            if(curS + a[i] > x) {
                curS = a[i];
                cnt += 1;
            } else {
                curS += a[i];
            }
        }
        return cnt <= 2;
    };
    int l = mx - 1, r = sum;
    while(l + 1 < r) {
        int mid = l + (r - l) / 2;
        if(check(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << r << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

