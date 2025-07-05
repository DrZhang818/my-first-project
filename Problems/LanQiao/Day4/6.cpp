#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


vector<int> prime;
vector<bool> ok(1001, true);
void init(){
    ok[1] = false;
    for(int i = 2; i <= 1000; i++){
        if(ok[i]){
            prime.push_back(i);
            for(int j = i * 2; j <= 1000; j += i){
                ok[j] = false;
            }
        }
    }
}
void solve(){
    ll n;
    cin >> n;
    ll ans = 0;
    for(ll i = (n%2?n-2:n-1); i > 1000; i -= 2){
        bool ok = true;
        for(auto c : prime){
            if(i % c == 0){
                ok = false;
                break;
            }
        }
        if(ok){
            ans = i;
            break;
        }
    }
    cout << ans << "\n";
}
    
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    init();
    solve();
    return 0;
}