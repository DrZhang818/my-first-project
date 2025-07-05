#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

void solve(){
    int n;
    cin >> n;
    vector<vector<int>> nums(n, vector<int>());
    for(int i = 0; i < n; i++){
        int k;
        cin >> k;
        nums[i].resize(k);
        for(int j = 0; j < k; j++){
            cin >> nums[i][j];
        }
    }
    int ans = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < nums[i].size(); j++){
            bool ok = false;
            for(int k = 0; k < nums[i][j]; k++){
                int x;
                cin >> x;
                if(x) ok = true;
            }
            if(ok) ans++;
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