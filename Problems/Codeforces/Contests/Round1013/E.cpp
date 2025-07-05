#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


vector<int> primes;
constexpr int MX = 10000005;
void sieve(){
    vector<bool> is_prime(MX + 1,true);
    is_prime[0] = is_prime[1] = false;

    for(int i = 2; i <= MX; i++){
        if(is_prime[i]){
            primes.push_back(i);
            for(int j = i * 2; j <= MX; j += i){
                is_prime[j] = false;
            }
        }
    }
}    
void solve() { 
    int n;
    cin >> n;
    unordered_set<int> st;
    ll ans = 0;
    for(auto c : primes) {
        if(c > n) break;
        ans += n / c;
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;

    sieve();
    while(t--) {
        solve();
    }
    return 0;
}
    
