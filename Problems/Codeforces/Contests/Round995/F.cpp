#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/2051/problem/F
/*
    模拟 || 分组思维 || 双指针
    题意:
        给你n张牌, 第m张为JOKER(大王牌), 以及q次询问
        每次询问会输入一个[1,n]范围内的整数x, 并将第x张牌放置牌堆顶部或底部
        求出每次询问后, JOKER的可能位置共有多少种?
    关键思考:
        1.每个牌的编号是不重要的, 可以仅仅关注JOKER, 把其他牌视为相同
        2.思考每次操作会让JOKER的位置怎么变化:
            一共有以下几种情况
            (1)操作的牌在JOKER之上, 那么操作后JOKER状态为x和x-1
            (2)操作的牌在JOKER之下, 那么操作后JOKER状态为x和x+1
            (3)操作的牌恰为JOKER, 那么JOKER的位置可能为1或n
            由此可得以下结论:
            ①可以记录JOKER的位置状态和当前操作位置的进行比较, 从而进行高效转移
            ②JOKER的位置只可能有以下三个情况: 在牌堆顶, 在m附近, 在牌堆底
            ③比较巧妙地是使用up记录牌堆顶的JOKER
                        使用l和r双指针记录中间位置的JOKER
                        使用down记录牌堆底的JOKER
*/
void solve(){
    ll n, m, q;
    cin >> n >> m >> q;
    ll l = m, r = m, up = -1, down = -1, ans = 0;
    for(int _ = 0; _ < q; _++){
        ll x;
        cin >> x;
        if(up != -1 && x > up) up++;
        if(down != -1 && x < down) down--;
        if(l != -1 && r != -1){
            if(x >= l && x <= r) {
                if(up == -1) up = 1;
                if(down == -1) down = n;
                if(l == r){
                    l = -1;
                    r = -1;
                }
            }
            else{
                if(x > r){
                    r++;
                }
                if(x < l){
                    l--;
                }
            }
        }
        if(l != -1 && r != -1){
            ans = r - l + 1;
            if(up != -1) ans += min(up, l - 1);
            if(down != -1) ans += n - max(down, r + 1) + 1;
        }
        else{
            ans = up < down ? up + n - down + 1 : n;
        }
        cout << ans << " ";
    }
    cout << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
