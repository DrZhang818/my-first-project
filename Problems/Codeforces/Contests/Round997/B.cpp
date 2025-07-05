#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n;
    cin >> n;
    vector<string> grid(n);
    for(int i = 0; i < n; i++){
        cin >> grid[i];
    }
    vector<int> ans;
    for(int i = 0; i < n; i++){
        int cnt = 0;
        for(int j = 0; j <= i; j++){
            if(grid[i][j] == '1'){
                cnt++;
            }
        }
        ans.insert(ans.begin() + cnt, i + 1);
    }
    for(auto c : ans){
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