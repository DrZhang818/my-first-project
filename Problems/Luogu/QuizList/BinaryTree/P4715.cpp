#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://www.luogu.com.cn/problem/P4715
/*


*/
void solve(){
    int n;
    cin >> n;
    int tot = 1 << (n + 1);
    vector<int> val(tot), winner(tot);
    for(int i = 0; i < (1 << n); i++){
        cin >> val[i + (1 << n)];
        winner[i + (1 << n)] = i + 1;
    }
    auto dfs = [&](auto&& dfs, int x){
        if(x >= 1 << n){
            return ;
        }
        dfs(dfs, 2 * x);
        dfs(dfs, 2 * x + 1);
        int val_l = val[2 * x], val_r = val[2 * x + 1];
        if(val_l > val_r){
            val[x] = val_l;
            winner[x] = winner[2 * x];
        }else{
            val[x] = val_r;
            winner[x] = winner[2 * x + 1];
        }
    };
    dfs(dfs, 1);
    cout << (val[2] > val[3] ? winner[3] : winner[2]) << "\n"; 
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}