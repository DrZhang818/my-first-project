#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


struct info{
    int l, r;
};
unordered_set<int> col;
class SegmentTree{
private:
    int n;
    vector<ll> change;
    vector<bool> updateArr;
    void down(int i){
        if(updateArr[i]){
            updateLazy(i << 1, change[i]);
            updateLazy(i << 1 | 1, change[i]);
            updateArr[i] = false;
            change[i] = 0;
        }
    }
    void updateLazy(int i, ll v){
        change[i] = v;
        updateArr[i] = true;
    }
    void updateHelp(int ul, int ur, ll v, int l, int r, int i){
        if(ul <= l && r <= ur){
            updateLazy(i, v);
        }else{
            int mid = (l + r) >> 1;
            down(i);
            if(ul <= mid){
                updateHelp(ul, ur, v, l, mid, i << 1);
            }
            if(ur > mid){
                updateHelp(ul, ur, v, mid + 1, r, i << 1 | 1);
            }
        }
    }
    void queryHelp(int ql, int qr, int l, int r, int i){
        if(l == r){
            if(change[i]) col.insert(change[i]);
            return;
        }
        down(i);
        int mid = (l + r) >> 1;
        if(ql <= mid){
            queryHelp(ql, qr, l, mid, i << 1);
        }
        if(qr > mid){
            queryHelp(ql, qr, mid + 1, r, i << 1 | 1);
        }
    }
public:

    SegmentTree(int x){
        n = x;
        change.resize(n << 2, 0);
        updateArr.resize(n << 2, false);
    }
    void update(int l, int r, ll v){
        updateHelp(l, r, v, 0, n - 1, 1);
    }
    void query(int ql, int qr){
        queryHelp(ql, qr, 0, n - 1, 1);
    }
};

void solve(){
    int n, m;
    cin >> n >> m;
    vector<info> pos(m);
    set<int> st;
    for(int i = 0; i < m; i++){
        cin >> pos[i].l >> pos[i].r;
        st.insert(pos[i].l);
        st.insert(pos[i].r);
    }
    st.insert(n);
    unordered_map<int, int> mp;
    int cur = 0;
    for(auto it : st){
        mp[it] = cur;
        cur += 2;
    }
    SegmentTree tree(cur);
    for(int p = 0; p < m; p++){
        int l = mp[pos[p].l];
        int r = mp[pos[p].r];
        tree.update(l, r, p + 1);
    }
    tree.query(0, mp[n]);
    cout << col.size() << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);


    solve();
    return 0;
}