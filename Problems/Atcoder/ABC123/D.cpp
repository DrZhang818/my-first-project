#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 30000000005;

//https://atcoder.jp/contests/abc123/tasks/abc123_d
/*
    贪心 || 枚举 || 搜索
    题意:
        给定三个序列A,B,C, 长度分别为X,Y,Z
        你需要输出A[i] + B[j] + C[k]的前ord大的值
        范围: X,Y,Z∈[1,1000], ord∈[1,min(3000, X*Y*Z)], A[i],B[i],C[i]∈[1,1e10]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        一个经典问题是: 给定两个序列A,B, 求A[i] + B[j]的第ord大
        这个问题的复杂度是O(NlogM), 我们可以二分答案x, check是否有 >= ord个数 >= x
        因此一个自然想法是把这个思路用到本题
        本题的关键点在于数据量比较小, 因此我们可以先把B,C数组的所有组合B[i] + C[j]算出来, 得到一个
        更大的数组D
        然后把A,D按照上述做法求出第ord大, 然后再推出前ord大
        但我们有更简单的贪心做法
        当我们求出数组D后, 我们思考: 哪些数和A组合会得到前ord大呢?
        显然, D得到的Y * Z个数中, 只有前ord个是有用的
        那么我们对D进行剪枝后, 就只剩下最多ord个数
        X * ord <= 3e6
        因此我们可以再次把A,D进行组合, 然后排序得到前ord个数, 这便是答案

        我们也可以使用BFS来求解, 首先把a,b,c降序排序
        当a[i] + b[j] + c[k]为第m大时
        第m + 1大不可能比a[i + 1] + b[j] + c[k] / a[i] + b[j + 1] + c[k] / a[i]+b[j]+c[k+1]更小
        这表明我们的解空间是有限的, 且每步可扩展的新状态最多3个
        利用堆 + set去重, 我们就可以做到O(klogk)的时间复杂度
*/

void solve1() {
    int x, y, z, ord;
    cin >> x >> y >> z >> ord;
    vector<ll> a(x + 1), b(y + 1), c(z + 1);
    for(int i = 1; i <= x; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= y; i++) {
        cin >> b[i];
    }
    for(int i = 1; i <= z; i++) {
        cin >> c[i];
    }
    sort(a.begin() + 1, a.end(), greater<ll>());
    sort(b.begin() + 1, b.end(), greater<ll>());
    sort(c.begin() + 1, c.end(), greater<ll>());
    using t4 = tuple<ll,int,int,int>;
    using t3 = tuple<int,int,int>;
    priority_queue<t4> q;
    set<t3> st;
    q.push({a[1] + b[1] + c[1], 1, 1, 1});
    st.insert({1, 1, 1});
    ll ans = 0;
    for(int s = 1; s <= ord; s++) {
        auto [cur, i, j, k] = q.top();
        q.pop();
        cout << cur << "\n";
        if(i + 1 <= x) {
            t3 nxt = {i + 1, j, k};
            if(!st.contains(nxt)) {
                st.insert(nxt);
                q.push({a[i + 1] + b[j] + c[k], i + 1, j, k});
            }
        }
        if(j + 1 <= y) {
            t3 nxt = {i, j + 1, k};
            if(!st.contains(nxt)) {
                st.insert(nxt);
                q.push({a[i] + b[j + 1] + c[k], i, j + 1, k});
            }
        }
        if(k + 1 <= z) {
            t3 nxt = {i, j, k + 1};
            if(!st.contains(nxt)) {
                st.insert(nxt);
                q.push({a[i] + b[j] + c[k + 1], i, j, k + 1});
            }
        }
    }
}

void solve() {
    int x, y, z, ord;
    cin >> x >> y >> z >> ord;
    vector<ll> a(x + 1), b(y + 1), c(z + 1);
    for(int i = 1; i <= x; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= y; i++) {
        cin >> b[i];
    }
    for(int i = 1; i <= z; i++) {
        cin >> c[i];
    }
    vector<ll> val;
    for(int i = 1; i <= y; i++) {
        for(int j = 1; j <= z; j++) {
            val.push_back(b[i] + c[j]);
        }
    }
    sort(val.begin(), val.end(), greater<ll>());
    vector<ll> ans;
    for(int i = 1; i <= x; i++) {
        for(int j = 0; j < val.size() && j < ord; j++) {
            ans.push_back(a[i] + val[j]);
        }
    }
    sort(ans.begin(), ans.end(), greater<ll>());
    for(int i = 0; i < ord; i++) {
        cout << ans[i] << "\n";
    }
}

// void solve() {
//     int x, y, z, ord;
//     cin >> x >> y >> z >> ord;
//     vector<ll> a(x + 1), b(y + 1), c(z + 1);
//     for(int i = 1; i <= x; i++) {
//         cin >> a[i];
//     }
//     for(int i = 1; i <= y; i++) {
//         cin >> b[i];
//     }
//     for(int i = 1; i <= z; i++) {
//         cin >> c[i];
//     }
//     sort(a.begin() + 1, a.end());
//     vector<ll> val;
//     for(int i = 1; i <= y; i++) {
//         for(int j = 1; j <= z; j++) {
//             val.push_back(b[i] + c[j]);
//         }
//     }    
//     sort(val.begin(), val.end());
//     auto ck = [&](ll x, int k) -> bool {
//         ll cnt = 0;
//         for(int i = a.size() - 1; i >= 1; i--) {
//             auto it = lower_bound(val.begin(), val.end(), x - a[i]) - val.begin();
//             cnt += val.size() - it;
//         }
//         return cnt >= k;
//     };
//     ll l = 0, r = inf;    
//     while(l + 1 < r) {
//         ll mid = l + r >> 1;
//         if(ck(mid, ord)) {
//             l = mid;
//         } else {
//             r = mid;
//         }
//     }
//     ll mn = l;
//     vector<ll> ans;
//     for(int i = 1; i < a.size(); i++) {
//         auto it = lower_bound(val.begin(), val.end(), mn - a[i]) - val.begin();
//         for(int j = it; j < val.size(); j++) {
//             ans.push_back(a[i] + val[j]);
//         }
//     }
//     sort(ans.begin(), ans.end(), greater<ll>());
//     for(int i = 0; i < ord; i++) {
//         cout << ans[i] << "\n";
//     }
// }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve1();
    }
    return 0;
}