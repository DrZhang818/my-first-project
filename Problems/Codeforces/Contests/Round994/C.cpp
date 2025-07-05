#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n, x, y;
    cin >> n >> x >> y;
    if(x > y) swap(x, y);
    vector<int> nums(n);
    nums[x - 1] = 0;
    nums[y - 1] = (y - x) % 2 == 0 ? 2 : 1;
    for(int i = x; i < x + n - 1; i++){
        int p = i % n;
        if(p == y - 1) continue;
        if(nums[(p + n - 1) % n] == 0){
            nums[p] = 1;
        }
        else{
            nums[p] = 0;
        }
        if((p + 1) % n == x - 1){
            if(nums[(p + n - 1) % n] == 1){
                nums[p] = 2;
            }else{
                nums[p] = 1;
            }
        }
    }
    for(int i = 0; i < n ; i++) cout << nums[i] << " ";
    cout << "\n";
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
