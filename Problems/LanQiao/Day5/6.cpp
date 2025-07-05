#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int s, n, lo, hi;
    cin >> s >> n >> lo >> hi;
    if(s < lo * n || s > hi * n){
        cout << -1 << "\n";
        return ;
    }
    int m = s / n;
    vector<int> ans(n, m);
    ans[n - 1] = s - (n - 1) * m;
    int l = 0, r = n - 1;
    while(l < r){
        int del = min(ans[l] - lo, hi - ans[r]);
        ans[l] -= del;
        ans[r] += del;
        if(ans[l] == lo) l++;
        if(ans[r] == hi) r--; 
    }
    for(int i = 0; i < n; i++){
        cout << ans[i] << " ";
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}