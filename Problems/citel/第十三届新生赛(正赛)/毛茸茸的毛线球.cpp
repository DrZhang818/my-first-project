#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


struct info{
    ll l, r, val, id;
};
void solve(){
    int n;
    cin >> n;
    //读入
    vector<info> seg(n);
    for(int i = 0; i < n; i++){
        cin >> seg[i].r >> seg[i].l >> seg[i].val;
        seg[i].id = i + 1;
    }
    //排序
    sort(seg.begin(), seg.end(), [](const info &a, const info &b){
        return a.r < b.r;
    });
    //二分查找
    auto bs = [&](int i) -> int {
        int l = -1, r = i;
        while(l + 1 < r){
            int mid = l + (r - l) / 2;
            if(seg[mid].r <= seg[i].l){
                l = mid;
            }else{
                r = mid;
            }
        }
        return l;
    };
    
    vector<ll> dp(n);
    vector<int> pre(n, -1);
    for(int i = 0; i < n; i++){
        pre[i] = bs(i);
        if(i == 0) dp[i] = seg[i].val;
        else dp[i] = max(dp[i - 1], (pre[i] == -1 ? 0 : dp[pre[i]]) + seg[i].val);
    }
    ll mx = n > 0 ? dp[n - 1] : 0;
    vector<int> sel;
    int i = n - 1;
    while(i >= 0){
        ll cur = seg[i].val + (pre[i] == -1 ? 0 : dp[pre[i]]);
        if(cur > (i > 0 ? dp[i - 1] : 0)){
            sel.push_back(seg[i].id);
            i = pre[i];
        }
        else{
            i -= 1;
        }
    }
    cout << (int)sel.size() << " " << mx << "\n";
    for(auto c : sel){
        cout << c << " ";
    }
    cout << "\n";
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