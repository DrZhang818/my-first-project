#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;


void solve(){
    int n;
    cin >> n;
    vector<int> nums(n);
    unordered_map<int, int> hash;
    int count = 0;
    for(int i = 0; i < n; i++){
        cin >> nums[i];
        hash[nums[i]]++;
        if(nums[i] == 1) count++;
    }
    cout << count << "\n";
    vector<int> ans(count);
    sort(nums.begin(), nums.end());
    for(int i = n - 1; i >= 0; i--){
        if(hash[nums[i]] > 0){
            ans[count - 1] = nums[i];
            for(int p = 1; p * p <= nums[i]; p++){
                if(nums[i] % p == 0){
                    hash[p]--;
                    if(p * p != nums[i]){
                        hash[nums[i] / p]--;
                    }
                }
            }
            count--;
        }
        if(count <= 0) break;
    }
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << (i == ans.size() - 1 ? "\n" : " ");
    }
}

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    return 0;
}