#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://www.luogu.com.cn/problem/P3369
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
    void up(int o) {
        siz[o] = siz[ls[o]] + siz[rs[o]] + key_cnt[o];
        dif[o] = dif[ls[o]] + dif[rs[o]] + (key_cnt[o] > 0);
    }
    void inorder(int o) {
        if(o != 0) {
            inorder(ls[o]);
            if(key_cnt[o] > 0) {
                collect[++ci] = o;
            }
            inorder(rs[o]);
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
    bool balance(int o) {
        return ALPHA * dif[o] >= max(dif[ls[o]], dif[rs[o]]);
    }
    void add_help(int o, int _fa, int _side, int x) {
        if(o == 0) {
            if(_fa == 0) {
                head = init(x);
            } else if(_side == 1) {
                ls[_fa] = init(x); 
            } else {
                rs[_fa] = init(x);
            }
        } else {
            if(key[o] == x) {
                key_cnt[o]++;
            } else if(key[o] > x) {
                add_help(ls[o], o, 1, x);
            } else {
                add_help(rs[o], o, 2, x);
            }
            up(o);
            if(!balance(o)) {
                top = o;
                fa = _fa;
                side = _side;
            }
        }
    }
    int small(int o, int x) {
        if(o == 0) {
            return 0;
        }
        if(key[o] >= x) {
            return small(ls[o], x);
        } else {
            return siz[ls[o]] + key_cnt[o] + small(rs[o], x);
        }
    }
    int index_help(int o, int rank) {
        if(siz[ls[o]] >= rank) {
            return index_help(ls[o], rank);
        } else if(siz[ls[o]] + key_cnt[o] < rank){
            return index_help(rs[o], rank - siz[ls[o]] - key_cnt[o]);
        } 
        return key[o];
    }
    void remove_help(int o, int _fa, int _side, int x) {
        if(key[o] == x) {
            key_cnt[o]--;
        } else if(key[o] > x) {
            remove_help(ls[o], o, 1, x);
        } else {
            remove_help(rs[o], o, 2, x);
        }
        up(o);
        if(!balance(o)) {
            top = o;
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
    ScapegoatTree sgt(n);
    for(int i = 0; i < n; i++) {
        int flag, x;
        cin >> flag >> x;
        if(flag == 1) {
            sgt.add(x);
        } 
        else if(flag == 2) {
            sgt.remove(x);
        }
        else if(flag == 3) {
            cout << sgt.getRank(x) << "\n";
        }
        else if(flag == 4) {
            cout << sgt.index(x) << "\n";
        }
        else if(flag == 5) {
            cout << sgt.pre(x) << "\n";
        }
        else {
            cout << sgt.post(x) << "\n";
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
    
