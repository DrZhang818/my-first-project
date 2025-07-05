#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


constexpr db ALPHA = 0.7;
class ScapegoatTree {
private:
    int head, cnt, ci, top, fa, side;
    vector<int> key, key_cnt, ls, rs, siz, dif, collect;
    int init(int x) {
        key[++cnt] = x;
        ls[cnt] = rs[cnt] = 0;
        key_cnt[cnt] = siz[cnt] = dif[cnt] = 1;
        return cnt;
    }
    void up(int i) {
        siz[i] = siz[ls[i]] + siz[rs[i]] + key_cnt[i];
        dif[i] = dif[ls[i]] + dif[rs[i]] + (key_cnt[i] > 0);
    }
    void inorder(int i) {
        if(i != 0) {
            inorder(ls[i]);
            if(key_cnt[i] > 0) {
                collect[++ci] = i;
            }
            inorder(rs[i]);
        }
    }
    int build(int l, int r) {
        if(l > r) {
            return 0;
        }
        int mid = (l + r) / 2;
        int h = collect[mid];
        ls[h] = build(l, mid - 1);
        rs[h] = build(mid + 1, r);
        up(h);
        return h;
    }
    void rebuild() {
        if(top != 0) {
            ci = 0;
            inorder(top);
            if(ci > 0) {
                if(fa == 0) {
                    head = build(1, ci);
                } else if(side == 1) {
                    ls[fa] = build(1, ci);
                } else {
                    rs[fa] = build(1, ci);
                }
            }
        }
    }
    bool balance(int i) {
        return ALPHA * dif[i] >= max(dif[ls[i]], dif[rs[i]]);
    }
    void add_help(int i, int _fa, int _side, int x) {
        if(i == 0) {
            if(_fa == 0) {
                head = init(x);
            } else if(_side == 1) {
                ls[_fa] = init(x); 
            } else {
                rs[_fa] = init(x);
            }
        } else {
            if(key[i] == x) {
                key_cnt[i]++;
            } else if(key[i] > x) {
                add_help(ls[i], i, 1, x);
            } else {
                add_help(rs[i], i, 2, x);
            }
            up(i);
            if(!balance(i)) {
                top = i;
                fa = _fa;
                side = _side;
            }
        }
    }
    int small(int i, int x) {
        if(i == 0) {
            return 0;
        }
        if(key[i] >= x) {
            return small(ls[i], x);
        } else {
            return siz[ls[i]] + key_cnt[i] + small(rs[i], x);
        }
    }
    int index_help(int i, int rank) {
        if(siz[ls[i]] >= rank) {
            return index_help(ls[i], rank);
        } else if(siz[ls[i]] + key_cnt[i] < rank){
            return index_help(rs[i], rank - siz[ls[i]] - key_cnt[i]);
        } 
        return key[i];
    }
    void remove_help(int i, int _fa, int _side, int x) {
        if(key[i] == x) {
            key_cnt[i]--;
        } else if(key[i] > x) {
            remove_help(ls[i], i, 1, x);
        } else {
            remove_help(rs[i], i, 2, x);
        }
        up(i);
        if(!balance(i)) {
            top = i;
            fa = _fa;
            side = _side;
        }
    }
public:
    ScapegoatTree(int n) {
        head = cnt = 0;
        key.resize(n + 1);
        key_cnt.resize(n + 1);
        ls.resize(n + 1);
        rs.resize(n + 1);
        siz.resize(n + 1);
        dif.resize(n + 1);
        collect.resize(n + 1);
    }
    void add(int x) {
        top = fa = side = 0;
        add_help(head, 0, 0, x);
        rebuild();
    }
    int getRank(int x) {
        return small(head, x) + 1;
    }   
    int index(int rank) {
        return index_help(head, rank);
    }   
    int pre(int x) {
        int kth = getRank(x);
        if(kth == 1) {
            return INT_MIN;
        } else {
            return index(kth - 1);
        }
    }   
    int post(int x) {
        int kth = getRank(x + 1);
        if(kth == siz[head] + 1) {
            return INT_MAX;
        } else {
            return index(kth);
        }
    }       
    void remove(int x) {
        if(getRank(x) != getRank(x + 1)) {
            top = fa = side = 0;
            remove_help(head, 0, 0, x);
            rebuild();
        }
    }
};  


void solve() { 
    int n;
    cin >> n;
    ScapegoatTree a(n);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a.add(x);
        if(i & 1) {
            cout << a.index((i + 1) / 2) << "\n";
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
    
