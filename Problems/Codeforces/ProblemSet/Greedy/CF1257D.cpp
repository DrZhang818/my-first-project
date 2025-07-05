#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/problemset/problem/1257/D
/*
    贪心 || 后缀最值
    题意:
        给定长度为n的数组代表一维数轴上的n个连续的点, a[i]代表该点的权值,
        以及m种(每种有无限条)带权线段, 每条线段由权值p和长度s组成
        你需要利用这m种线段覆盖给定的n个点, 并满足每条线段的权值大于等于覆盖区间内的点的最大值
        最小化覆盖所需的条数
    关键思考:
        首先, 最好想到的一个性质就是
        (1)对于长度相同的多条线段, 一定是选权值最大的那一个
            因此在读入阶段就可以按照长度分类, 并保留权值最大的
        本题最关键的一个点就在于, 为什么从左到右贪是正确的
        这就等价于一个问题: 为什么对于每一个点都是能往右扩多少就扩多少
        其实是很简单的一个问题, 我们可以用集合的角度来思考
        假设对于某个左端点L, 其最大能够扩展到R
        ①L.....R[    ], 我们剩下要解决的问题就是[    ]如何选取, 长度是n-R-1, 假如我们不扩展到R呢?
        ②L..r[..R    ], 这样我们要解决的长度显然更长, 因为①包含在②之内, ②相比①一定是不优的
        因此就得到了本题最重要的一个贪心性质
        (2)对于每个左端点来说, 能扩多少就扩到多少
            这样问题就变成如何高效计算每个左端点能扩展到哪儿了
        (3)为了高效解决性质(2), 我们思考一个新的性质
            如果长度为s的线段可以解决长度为p的权值, 那么长度为s-1的线段一定也可以解决
            因为我们可以借用长度为s的来解决长度为s-1的
            这就可以利用后缀最值数组来计算出长度为len时最大可以解决的权值
        在以上性质的加持下, 我们可以利用枚举右维护左的技巧, 边遍历边维护窗口内最大权值cur和窗口长度len
        如果遇到hero[len] < cur就代表不能再扩展了, 此时就需要使用新的线段来覆盖了
        代码实现时, 特判hero[1] < cur的情况, 这代表任何线段的权值都比不过cur, 答案即为非法值-1
*/
void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int m;
    cin >> m;
    vector<int> hero(n + 1);
    for(int i = 0; i < m; i++){
        int p, s;
        cin >> p >> s;
        hero[s] = max(hero[s], p);
    }
    for(int i = n - 1; i >= 1; i--){
        hero[i] = max(hero[i + 1], hero[i]);
    }
    int cur = 0, len = 0, ans = 1;
    for(int i = 0; i < n; i++){
        cur = max(cur, a[i]);
        if(hero[1] < cur){
            cout << -1 << "\n";
            return;
        }
        len++;
        if(hero[len] < cur) {
            ans++;
            len = 1;
            cur = a[i];
        }
    }
    cout << ans << "\n";
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

