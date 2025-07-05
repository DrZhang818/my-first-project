#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://citel.bjtu.edu.cn/acm/problem/2030
/*
    数据结构 || 模拟
    题意: 每次选一个点x, 将x - i的点转移到x + i(或者反过来)
        由于我们每次操作至多对"当前总长度"的一半进行操作,
        所以最终遍历的次数收敛于n
        只需要维护好当前窗口的左端点和右端点即可
    关键思考:
        怎样高效的实现转移操作?
        可以把处在同一状态下的点用fa数组存储, 后续更新只需要更新fa数组即可
        这就用到了并查集这个数据结构
*/
void solve(){
    int n, m;
    cin >> n >> m;
    vector<int> fa(n + 2);
    for(int i = 1; i <= n + 1; i++){
        fa[i] = i;
    }
    function<int(int)> find_set = [&](int x) -> int{
        while(fa[x] != x){
            fa[x] = fa[fa[x]];
            x = fa[x];
        }
        return fa[x];
    };
    int lt = 1, rt = n;
    for(int i = 0; i < m; i++){
        int x;
        cin >> x;
        int leftLen = x - lt;
        int rightLen = rt - x;
        if(leftLen > rightLen){
            int l = x, r = x + rightLen;
            int cur = find_set(l);
            while(cur <= r){
                fa[cur] = 2 * x - cur;
                cur++;
            }
            rt = x;
        }
        else{
            int l = x - leftLen, r = x;
            int cur = find_set(l);
            while(cur <= r){
                fa[cur] = 2 * x - cur;
                cur++;
            }
            lt = x;
        }
    }
    for(int i = 1; i <= n; i++){
        int pos = find_set(i);
        cout << pos << " ";
    }
    cout << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}