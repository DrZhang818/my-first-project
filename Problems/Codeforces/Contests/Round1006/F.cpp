#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    auto dfs = [&](auto &&dfs, int l, int r) -> void {
        if(l == r) {
            a[l] = k;
            return;
        }
        int s = log2(r - l + 1);
        if((1 << s) == r - l + 1) s -= 1;
        int len = r - l + 1 - (1 << s);
        dfs(dfs, l, l + len - 1);
        dfs(dfs, r - len + 1, r);
        for(int i = l + len; i <= r - len; i++) {
            a[i] = 0;
        }
    };
    dfs(dfs, 1, n);
    for(int i = 1; i <= n; i++) {
        cout << a[i] << " \n"[i == n];
    }
    

}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
