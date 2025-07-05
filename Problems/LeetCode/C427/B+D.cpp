#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://leetcode.cn/problems/maximum-area-rectangle-with-point-constraints-ii/description/
/*
    离线询问 + 离散化 + 树状数组
    

*/
class Fenwick{
    vector<int> tree;
public:
    Fenwick(int n) : tree(n, 0){}
    void add(int i){
        while(i < tree.size()){
            tree[i]++;
            i += i & -i;
        }
    }
    int pre(int i){
        int res = 0;
        while(i > 0){
            res += tree[i];
            i -= i & -i;
        }
        return res;
    }
    int query(int l, int r){
        return pre(r) - pre(l - 1);
    }
};

struct Query{
    int x1, x2, y1, y2;
    ll area;
    Query(int a, int b, int c, int d, ll e) : x1(a), x2(b), y1(c), y2(d), area(e){}
};
struct Data{
    int qid, sign, y1, y2;
    Data(int a, int b, int c, int d) : qid(a), sign(b), y1(c), y2(d){}
};
void solve(){
    int n;
    cin >> n;
    vector<int> xCoord(n), yCoord(n);
    for(int i = 0; i < n; i++) cin >> xCoord[i];
    for(int i = 0; i < n; i++) cin >> yCoord[i];
    
    unordered_map<int, vector<int>> x_map, y_map;
    for(int i = 0; i < n; i++){
        x_map[xCoord[i]].push_back(yCoord[i]);
        y_map[yCoord[i]].push_back(xCoord[i]);
    }
    unordered_map<ll, int> below;
    for(auto &[x, ys] : x_map){
        sort(ys.begin(), ys.end());
        for(int i = 1; i < ys.size(); i++){
            below[(ll)x << 32 | ys[i]] = ys[i - 1];
        }   
    }
    unordered_map<ll, int> left;
    for(auto &[y, xs] : y_map){
        sort(xs.begin(), xs.end());
        for(int i = 1; i < xs.size(); i++){
            left[(ll)xs[i] << 32 | y] = xs[i - 1];
        }
    }
    vector<int> xs;
    for(auto &[x, _] : x_map){
        xs.push_back(x);
    }
    sort(xs.begin(), xs.end());

    vector<int> ys;
    for(auto &[y, _] : y_map){
        ys.push_back(y);
    }
    sort(ys.begin(), ys.end());

    vector<Query> queries;
    for(auto &[x2, list_y] : x_map){
        for(int i = 1; i < list_y.size(); i++){
            int y2 = list_y[i];
            auto it = left.find((ll)x2 << 32 | y2);
            if(it == left.end()){
                continue;
            }
            int x1 = it->second;
            int y1 = list_y[i - 1];
            it = left.find((ll)x2 << 32 | y1);
            if(it == left.end() || it->second != x1){
                continue;
            }
            it = below.find((ll)x1 << 32 | y2);
            if(it == left.end() || it->second != y1){
                continue;
            }
            queries.emplace_back(
                lower_bound(xs.begin(), xs.end(), x1) - xs.begin(),
                lower_bound(xs.begin(), xs.end(), x2) - xs.begin(),
                lower_bound(ys.begin(), ys.end(), y1) - ys.begin(),
                lower_bound(ys.begin(), ys.end(), y2) - ys.begin(),
                (ll)(x2 - x1) * (y2 - y1)
            );
        }
    }

    for(auto &q : queries){
        cout << q.x1 << " " << q.x2 << " " << q.y1 << " " << q.y2 << " " << q.area << endl;
    }

    vector<vector<Data>> qs(xs.size());
    for(int i = 0; i < queries.size(); i++){
        auto& [x1, x2, y1, y2, _] = queries[i];
        if(x1 > 0){
            qs[x1 - 1].emplace_back(i, -1, y1, y2);
        }
        qs[x2].emplace_back(i, 1, y1, y2);
    }
    cout << "\n";
    for(auto &q : qs){
        for(auto &p : q){
            cout << p.qid << " " << p.sign << " " << p.y1 << " " << p.y2 << endl;
        }
    }
    vector<int> res(queries.size());
    Fenwick tree(ys.size() + 1);
    for(int i = 0; i < xs.size(); i++){
        for(int y : x_map[xs[i]]){
            tree.add(lower_bound(ys.begin(), ys.end(), y) - ys.begin() + 1);
        }
        for(auto& [qid, sign, y1, y2] : qs[i]){
            res[qid] += sign * tree.query(y1 + 1, y2 + 1);
        }
    }
    for(auto num : res){
        cout << num << "\n";
    }
    ll ans = -1;
    for(int i = 0; i < res.size(); i++){
        if(res[i] == 4){
            ans = max(ans, queries[i].area);
        }
    }
    //cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
  
    solve();
    return 0;
}