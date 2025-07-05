/*
    BST——替罪羊树
    替罪羊树是有序表的一种, 支持动态插入、删除、查询的功能, 通过失衡因子维护BST的平衡性
    下面给出各变量的意义:
    head: 树的根节点
    cnt:  树的节点个数
    ci:   collect栈收集到的失衡节点个数
    top:  最上方的失衡子树的根节点
    fa:   top的父节点
    side: 标记top位于fa的左/右, 即失衡方向
    下面给出各数组的意义:
    key[]: 键
    key_cnt[]: 键的值, 这里记录的是次数
    ls[]:  i的左儿子
    rs[]:  i的右儿子
    siz[]: 以i为根的子树的点权和(cnt为节点权值)
    dif[]: 以i为根的子树的节点数量
    collect[]: 是一个单调递减栈, 收集失衡元素
    下面介绍各函数的实现原理:
    init(): 元素x没有在树中, 为x分配一个新的空间
    up()  : 左右子树信息变化后, 更新父节点信息
    inorder(): 以节点i为根进行中序遍历, 收集key_cnt不为0的节点(注意是懒更新, 可能x存在与key中但cnt为0)
    build(): 对collect收集到的元素进行二分建树
    rebuild(): 如果发生失衡, 重新建树
    balance(): 判断是否失衡
    add_help(): 寻找key为x的节点并将cnt加1, 如果没找到就init, 过程中如果失衡就要收集失衡信息
                由于是自上而下递归, 因此是失衡信息一定是第一颗开始失衡的树
    small(): 求以i为根的子树中比x小的点权和
    index_help(): 求解以i为根的子树中, 排名为rank的key
    remove_help(): 懒删除, 将x的key_cnt减1
    
    关键思考:
        替罪羊树的核心是不平衡率, 当设计到add和remove的时候, 改变了树的形状
        就需要通过不平衡率判断是否需要重建
        作为树形结构, 替罪羊树采用ls,rs的方式存储节点
        每个节点的信息包括键值对, 出现次数
        add 方法利用二分定位, 这是构建BST的基本方法
            特殊之处在于添加后我们需要判断以当前节点为根的子树是否平衡
            由于递归序的原因, 我们自动得到了最上方的不平衡的子树
        remove 方法利用了二分 + lazy_tag技术
            删除节点同样可能导致失衡, 因此也许要判断是否需要重新建树
        balance 方法是判断失衡的核心代码
            当i节点的重量倾向一个儿子的时候, 就需要重建
        rebuild 方法仅当top不为0(虚拟头)时进行
            首先通过中序遍历收集需要重构的节点
            然后根据side判断top位于fa的哪一侧, 接着调用build即可
        build 方法即对收集到的节点进行二分重构
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


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

