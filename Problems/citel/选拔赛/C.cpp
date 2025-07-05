#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

void solve(){
    int n;
    cin >> n;
    int len = n * (n - 1) / 2 - 1;
    vector<int> nums(len);
    for(int i = 0; i < len; i++){
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());
    if(nums[0] == nums[1]){
        cout << "Infinite\n";
        return;
    }
    nums.push_back(-1);
    int cur = 1;
    int ans = 0;
    for(int l = 0; l <= len;){
        int r = l;
        int curNum = nums[l];
        bool find = false;
        while(r < l + cur){
            if(nums[r] != curNum){
                ans = curNum;
                find = true;
                break;
            }
            r++;
        }
        if(find){
            break;
        }
        cur++;
        l = r;
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