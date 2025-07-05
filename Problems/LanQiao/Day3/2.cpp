#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


struct FenwickTree{
    int n;
    vector<int> tree;
    FenwickTree(int size) : n(size), tree(n + 1, 0) {}
    void update(int idx, int val){
        while(idx <= n){
            tree[idx] ^= val;
            idx += idx & (-idx);
        }
    }
    int query(int idx) const {
        int res = 0;
        int i = idx;
        while(i > 0){
            res ^= tree[i];
            i -= i & (-i);
        }
        return res;
    }
};
void solve(){
    int n, m;
    cin >> n >> m;
    FenwickTree ft(n);
    while(m--){
        int flag, l, r;
        cin >> flag >> l >> r;
        if(flag == 1){
            ft.update(l, 1);
            ft.update(r + 1, 1);
        }
        else if(flag == 2){
            int cur = ft.query(r) ^ ft.query(l - 1);
            if(cur){
                cout << "Yes\n";
            }else{
                cout << "No\n";
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}