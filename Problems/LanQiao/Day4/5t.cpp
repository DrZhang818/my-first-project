#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    unordered_map<int, int> maxRange;  // 记录每个数的最大区间长度
    set<int> f_values;  // 用来存储所有不同的 f(i) 值

    // 从后往前遍历
    for (int i = n - 1; i >= 0; i--) {
        int num = a[i];
        int max_len = 1;  // 当前数至少能组成一个长度为 1 的区间（就是它本身）

        // 检查它的倍数
        for (int j = num * 2; j <= 1e6; j += num) {
            if (maxRange.find(j) != maxRange.end()) {
                max_len = max(max_len, maxRange[j] + 1);
            }
        }

        // 更新 maxRange 中该数的最长区间
        maxRange[num] = max_len;

        // 将这个 f(i) 值加入集合
        f_values.insert(max_len);
    }

    // 输出不同的 f(i) 值的个数
    cout << f_values.size() << "\n";
}
    
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}