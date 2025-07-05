#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://citel.bjtu.edu.cn/acm/problem/2063
/*
    贪心 && 单调栈 && 树状数组 && 离线查询
    cf 1700 ~ 1900
    

*/
struct Query{
    int l, r, idx;
};

struct Point{
    int x, y;
};

struct FenwickTree{
    int size;
    vector<int> tree;
    FenwickTree(int n) : size(n), tree(n + 2, 0) {} 
    void update(int idx, int delta = 1){
        while(idx <= size){
            tree[idx] += delta;
            idx += idx & -idx;
        }
    }
    int query(int idx) const{
        int res = 0;
        int i = idx;
        while(i > 0){
            res += tree[i];
            i -= i & -i;
        }
        return res;
    }
    int query(int l, int r) const{
        if(l > r) return 0;
        return query(r) - query(l - 1);
    }
};
void solve(){
    int n, q;
    cin >> n >> q;
    vector<int> b(n + 1);
    for(int i = 1; i <= n; i++){
        cin >> b[i];
    }
    vector<int> next_smaller(n + 1, n + 1);
    stack<int> stk;
    for(int i = n; i >= 1; i--){
        while(!stk.empty() && b[stk.top()] >= b[i]){
            stk.pop();
        }
        if(!stk.empty()){
            next_smaller[i] = stk.top();
        }
        stk.push(i);
    }
    vector<Point> points;
    for(int i = 1; i <= n; i++){
        if(next_smaller[i] <= n){
            points.push_back(Point{i, next_smaller[i]});
        }
    }
    vector<Query> queries_list(q);
    for(int i = 0; i < q; i++){
        cin >> queries_list[i].l >> queries_list[i].r;
        queries_list[i].idx = i;
    }
    sort(points.begin(), points.end(), [&](const Point &a, const Point &b){
        if(a.y != b.y) return a.y < b.y;
        return a.x < b.x;
    });
    sort(queries_list.begin(), queries_list.end(), [&](const Query &a, const Query &b){
        if(a.r != b.r) return a.r < b.r;
        return a.l < b.l;
    });
    vector<int> results(q, 0);
    FenwickTree ft(n);
    int p = 0;
    for(auto &query : queries_list){
        while(p < points.size() && points[p].y <= query.r){
            ft.update(points[p].x);
            p++;
        }
        results[query.idx] = ft.query(query.l, query.r);
    }
    for(int i = 0; i < q; i++){
        cout << results[i] << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}