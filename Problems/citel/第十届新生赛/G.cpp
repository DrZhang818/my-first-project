#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){   
    int n;
    cin >> n;
    int temp = n;
    int cnt = 0;
    int res = 1;
    for(int i = 2; i * i <= n; i++){
        cnt = 0;
        while(n % i == 0){
            n /= i;
            cnt++;
        }
        res *= (cnt + 1);
    }
    if(n > 1) res *= 2;
    
    if(temp % res == 0){
        cout << "YES" << endl;
    }
    else{
        cout << "NO" << endl;
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
