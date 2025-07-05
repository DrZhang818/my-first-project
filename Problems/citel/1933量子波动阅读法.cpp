#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

void solve(){
    int n, m, c;
    cin >> n >> m >> c;
    vector<int> count(500005);
    for(int i = 0; i < m; i++){
        int x;
        cin >> x;
        for(int p = 1; p * p <= x; p++){
            if(x % p == 0){
                count[p]++;
                if(p * p != x){
                    count[x / p]++;
                }
            }
        }
    }
    for(int i = 0; i < c; i++){
        int num;
        cin >> num;
        int ans = n / num;
        ans -= count[num];
        cout << ans << "\n";
    }
}   

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    return 0;
}