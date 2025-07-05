#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;

//https://citel.bjtu.edu.cn/acm/problem/1939
//本题注意 输出换行一定要用 "\n" 用 endl会TLE
vector<ll> nums;
vector<ll> prefix;
bool check(ll cnt, int start, ll x){

    ll end;
    if(x > 1e9){
        end = distance(nums.begin(), nums.end());
    }else{
        end = lower_bound(nums.begin() + start, nums.end(), x) - nums.begin();
    }

    if(end == start){
        return true;
    }
    
    ll sum = prefix[end] - prefix[start];
    
    return x <= (cnt + sum) / (end - start);
}
void solve(){
    ll x, y;
    cin >> x >> y;

    ll l = nums[y] - 1, r = nums[y] + x + 1;
    while(l + 1 < r){
        ll mid = l + ((r - l) >> 1);
        if(check(x, y, mid)){
            l = mid;
        }else{
            r = mid;
        }
    }
    cout << l << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    nums.resize(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());
    prefix.resize(n + 1);

    for(int i = 1; i <= n; i++){
        prefix[i] = prefix[i - 1] + nums[i - 1];
    }
    while(m--){
        solve();
    }
    return 0;
}