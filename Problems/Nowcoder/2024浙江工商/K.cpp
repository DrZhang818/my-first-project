#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

void solve(){
    int n, k;
    cin >> n >> k;
    std::vector<int> nums(n);
    vector<int> cnt(101, 0);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
        cnt[nums[i]]++;
    }   
    int ans = -1;
    for(int i = 1; i <= 100; i++){
        if(cnt[i] == k){
            ans = i;
        }
    }
    cout << ans << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}