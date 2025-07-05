#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/problemset/problem/1332/B
/*
    构造 || 数论
    题意:
        给定一个长度为n的合数数组, 你需要把数组分成最多11组, 使得:
        元素范围a[i]∈[4,1000]
        (1)每个元素属于且仅属于一个组
        (2)每组元素两两不互质
    关键思考:
        本题最关键的在于不需要最小化组数, 不用贪心就很容易利用分组解决了
        注意到性质(2)等价于整组元素gcd > 1
        这样就容易想到利用质因数进行分组了, 首先计算出质数, 然后从小到大分类即可
        注意到第11个质数31和第32个质数37的乘积 > 1000
        因此这个方法一定可以保证答案在11以内
*/
vector<int> prime;
vector<int> ok(101, true);
void init(){
    ok[1] = false;
    for(int i = 2; i <= 100; i++){
        if(ok[i]){
            prime.push_back(i);
            for(int j = i * 2; j <= 100; j += i){
                ok[i] = false;
            }
        }
    }
}
void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }   
    map<int,int> mp;
    vector<int> ans(n);
    int cnt = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < prime.size(); j++){
            if(a[i] % prime[j] == 0){
                if(mp[prime[j]] == 0){
                    cnt++;
                    mp[prime[j]] = cnt;
                }
                ans[i] = mp[prime[j]];
                break;
            }
        }
    }
    cout << cnt << "\n";
    for(int i = 0; i < n; i++){
        cout << ans[i] << " ";
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    prime.reserve(101);
    init();
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}