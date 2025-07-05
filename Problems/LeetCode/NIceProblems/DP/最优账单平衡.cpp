#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int sum = accumulate(a.begin(), a.end(), 0);
    vector<int> memo(1 << n, -1);
    auto dfs = [&](this auto&& dfs, int msk, int sum, int j) -> int {
        if(j == 1) {
            return 0;
        }
        int &res = memo[msk];
        if(res != -1) return res;
        res = 0;
        if(sum == 0) {
            for(int i = 0; i < n; i++) {
                if((msk & (1 << i)) == 0) {
                    res = dfs(msk | (1 << i), sum - a[i], j - 1) + 1;
                    break;
                }
            }
        }
        else{
            for(int i = 0; i < n; i++) {
                if((msk & (1 << i)) == 0) {
                    res = max(res, dfs(msk | (1 << i), sum - a[i], j - 1));
                }
            }
        }
        return res;
    };
    int ans = dfs(0, sum, n);
    cout << n - ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

