#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/1542/problem/B
/*
    构造 || 数学
    题意:
        给定整数a, b，定义集合set有以下性质:
        (1)1在集合内
        (2)若x在集合内, 则x * a, x + b也在集合内
        判断给定的整数n是否在集合内
    关键思考:
        由于可以把×a和+b看作两个操作, 那么相当于集合是以1为根节点的一个满二叉树，
        问题即判断n是否为树上的一个节点
        朴素想法是从n开始回溯, 时间复杂度为O(n/b), 需要优化
        性质探索:
        (1)假设只进行×a操作, 形成的集合为{a^k}
        (2)假设只进行+b操作, 形成的集合为{1+pb}
        (3)如果进行复合操作, 不妨设当前元素为x
            1.×a+b后, 变为ax+b
            2.+b×a后, 变为a(x+b)
        我们发现, 集合的元素总是可以写成a^k + pb的形式(k,p∈N)
        必要性(n在集合内, 则n一定满足a^k + pb的形式):
            1满足a^k + pb的形式
            当元素满足a^k + pb时
            (1)×a, 变为a^(k+1) + (pa)b -> 仍为a^k + pb的形式
            (2)+b, 变为a^k + (p+1)b    -> 仍为a^k + pb的形式
        充分性(n满足a^k + pb的形式, 则n一定在集合内)
            显然我们可以依次先进行k次×a操作, 再进行p次+b操作
        综上: n在集合内 <--> n满足a^k + pb的形式
    代码实现:
        注意要枚举k而不是枚举p
        枚举p的时间复杂度时O(n/b)
        枚举k的时间复杂度是(logk)
*/
//优化解法
void solve1(){
    ll n, a, b;
    cin >> n >> a >> b;
    bool ok = false;
    for(ll x = 1; x <= n; x *= a){
        if((n - x) % b == 0){
            ok = true;
            break;
        }
        if(a == 1){
            break;
        }
    }
    if(ok){
        cout << "Yes\n";
    }else{
        cout << "No\n";
    }
}

//比赛写法
void solve(){
    ll n, a, b;
    cin >> n >> a >> b;
    bool ok = false;
    if(a == 1){
        if((n - 1) % b == 0){
            ok = true;
        } 
    }
    else{
        while(1){
            ll t = 1;
            for(; t <= n; t *= a){
                if((n - t) % b == 0){
                    ok = true;
                    break;
                }
            }
            if(n % a != 0) break;
            n /= a;
        }
    }
    if(ok){
        cout << "YES\n";
    }else{
        cout << "NO\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    while(t--){
        solve1();
    }
    return 0;    
}
