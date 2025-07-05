#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/1497/problem/C2
/*
    构造 
    题意:
        给定两个整数n和k, 要求构造出一个长度为k的数组, 满足以下性质
        (1)∑a[i] == n
        (2)lcm(a) <= n // 2
        数据范围: 3 <= n <= 1e9, 3 <= k <= n
    关键思考:
        本题有easy版本, easy版本中的k固定为3
        不过如果没有easy版本如何思考呢？
        考虑到1和2这两个特殊的数:
        1是任何数的因子, 2是所有偶数的因子
        那么就可以考虑使用这两个数进行"修正"
        由于lcm不超过n//2, 一个自然想法就是使用两个大数(初始化为n//2), 剩下的数利用1和2进行修正
        例如6 4就是
        3 3 -> 1 1 2 2
        这个修正过程就是本题的思考核心
        可以发现如果直接思考如何把大数借给小数是非常麻烦的, 由于大数有两个, 小数也有两个(1和2)
        难点就在于我们要凑正好k个数, 如果这个k小一点是不是就简单了呢?
        于是本题的思想就是"大事化小", 去转化为更容易解决的子问题
        3个数来凑就非常简单了, 思想与上面一样, 但是这样把配凑k-2个数变成了3-2==1个数, 大大降低讨论难度
        接下来给出证明:
        首先输出k-3个1, 1是不影响lcm的, 相当于万金油
        问题就变成了(n-k+3, 3)这个子问题
        这个子问题的lcm <= (n-k+3) // 2 <= n // 2, 可以保证答案的正确性
        接着就是如何构造:
        比较好想的就是分奇偶性
        let m = n - k + 3
        1.当m是奇数时, {1, m/2, m/2}显然满足题意, 构造思想就是使用1来"修正"
        2.当m是偶数时, 我们发现m/2后的奇偶性也需要讨论, 也就是讨论m/4的奇偶性
            (1)m/4为奇数时, 得到的是{m/2, m/2}, 借鉴1.的思路, 修正为{2, m/2-1, m/2-1}
            (2)m/4为偶数时, 例如12 -> 6 6, 显然可以调整为{6, 3, 3}, 即{m/4, m/4, m/2}
*/
void solve(){
    int n, k;
    cin >> n >> k;
    while(k > 3){
        cout << 1 << " ";
        n--;
        k--;
    }
    if(n & 1){
        cout << 1 << " " << n / 2 << " " << n / 2 << "\n";
    }
    else if(n % 4 == 0){
        cout << n / 4 << " " << n / 4 << " " << n / 2 << "\n";
    }
    else{
        cout << 2 << " " << n / 2 - 1 << " " << n / 2 - 1 << "\n";
    }
}
/*void solve(){
    int n, k;
    cin >> n >> k;
    if(n % k == 0){
        for(int i = 0; i < k; i++){
            cout << n / k << " ";
        }
        cout << "\n";
        return;
    }
    if((n / 2) >= (n - k + 1)){
        for(int i = 0; i < k - 1; i++){
            cout << 1 << " ";
        }
        cout << n - k + 1 << "\n";
        return;
    }
    int cnt = (n - k + 1) - (n / 2);
    int end = n / 2;
    if((n / 2) % 2 == 1){
        end -= 1;
        cnt += 1;
    }
    if(cnt <= k){
        for(int i = 0; i < k - cnt - 1; i++){
            cout << 1 << " ";
        }
        for(int i = 0; i < cnt; i++){
            cout << 2 << " ";
        }
        cout << end << "\n";
        return;
    }
    int a = 2 * k - n  + 4;
    int b = -a;

    if(b % 2 == 0){

    }

}
*/
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