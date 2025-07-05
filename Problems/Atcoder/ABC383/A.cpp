#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

void solve(){
    int n;
    cin >> n;
    int t = 0, cur = 0;
    while(n--){
        int T, V;
        cin >> T >> V;
        cur = max(0, cur - T + t);
        t = T;
        cur += V;
    }
    cout << cur << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
  
    solve();
    
    return 0;
}