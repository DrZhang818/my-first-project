#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/contest/2059/problem/C
/*
    贪心思维 || 构造 
    题意:
        给定一个整数n表示有n条队列, 接下来有n个时刻, 每个时刻每条队都会加入一些人(范围是[1,300])
        同时每个时刻你可以选择一条队将该队人数清零
        设最后时刻的n条队分别有a1,a2,...,an个人
        求最大的MEX(ai)
    关键思考:
        由于MEX的性质, 如果要最大化MEX, 就要保证队列出现连续的0,1,2,...
        0一定是可以取到, 因为最后一时刻一定会把一条队清零
        由于每次加入的人是个正整数, 因此最后要想出现1, 只能是在n-1时刻清零并且第n个时刻加入1人
        出现2, 只能是n-2时刻清零并且在第n-1和第n个时刻都加入1人
        由此得到本题一个关键性质:
        (*)后缀连续1的个数是每个队伍能提供的最大贡献, 其余数据为垃圾数据
        假设我们获得了每个队的最大贡献, 如何分配顺序使得MEX最大呢?
        例如数组[2,3,1,1,4]
        贪心的想, 我们肯定希望小的数先做贡献, 大的数后做贡献, 大的数做小贡献就像田忌赛马一样
        因此先排序一下[1,1,2,3,4]
        我们要获得0, 就清除第一个1
        获得1, 就使用第二个1
        ...
        这样最终能得到MEX == 5
        换一个数据[1,1,1,3,5]
        我们发现第一个1可以使得ans变为1, 第二个1可以使得ans变为2, 而第三个1就不再起作用了
        然后我们希望有个数等于2, 但实际上并没有, 此时只能由3来牺牲一下, 提供2
        然后我们希望有个数等于3, 但实际上并没有, 此时只能由5来牺牲一下, 提供3
        最后得到MEX == 4
        所以我们实际上只需要判断cur是否大于等于ans即可, 如果大于ans, 那么ans可以+1, 否则不起作用
*/
void solve(){
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> a[i][j];
        }
    }
    vector<int> c(n);
    for(int i = 0; i < n; i++) {
        for(int j = n - 1; j >= 0; j--){
            if(a[i][j] == 1) {
                c[i]++;
            }else{
                break;
            }
        }
    }
    sort(c.begin(), c.end());
    int ans = 0;
    for(auto x : c) { 
        if(x >= ans) {
            ans += 1;
        }
    }
    cout << ans << "\n";
}

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

