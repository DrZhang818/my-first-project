#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n, a, b;
    cin >> n >> a >> b;
    vector<ll> nums(n);
    unordered_map<ll, int> mp;
    for(int i = 0; i < n; i++){
        cin >> nums[i];
        mp[nums[i]]++;
    }
    sort(nums.begin(), nums.end(), greater<ll>());
    db ans = 0;
    for(int i = 0; i < a; i++){
        ans += nums[i];
    }
    int cnt = 0;
    for(int i = a - 1; i >= 0; i--){
        if(nums[i] == nums[a - 1]){
            cnt++;
        }else{
            break;
        }
    }
    ans /= a;
    cout << fixed << setprecision(6) << ans << "\n";
    int tot = mp[nums[a - 1]];
    vector<ll> C(tot + 1);
    C[0] = 1;
    for(int i = 1; i <= tot; i++){
        C[i] = C[i - 1] * (tot - i + 1) / i;
    }
    ll c_ans = 0;
    if(cnt == a){
        for(int i = a; i <= min(tot, b); i++){
            c_ans += C[i];
        }
    }else{
        c_ans = C[cnt];
    }
    cout << c_ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}