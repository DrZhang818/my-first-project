#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;


void solve(){
    int n, q;
    cin >> n >> q;
    vector<int> nums(n);
    for(auto& num : nums){
        cin >> num;
    }

    for(int i = 0; i < q; i++){
        int x; 
        cin >> x;
        int cnt1 = count(nums.begin(), nums.end(), 1);
        int cnt0 = count(nums.begin(), nums.end(), 0);
        int cntn1 = count(nums.begin(), nums.end(), -1);
        if(cnt0 > 0 ){
            cout << "Yes\n";
            continue;
        }else if(cntn1 == 0){
            cout << "No\n";
            continue;
        }else{
            int high = (cntn1 - 1) / 2;
            if(3 * high >= cntn1 - cnt1){
                cout << "Yes\n";
            }else{
                cout << "No\n";
            }
        }
    }
}

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}