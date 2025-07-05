#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef __int128 i128;

constexpr ll M = 20240601000;
void solve() {
    i128 ans = 0;
    for(ll i = 1; i * i <= M; i++) {
        if(M % i == 0 && (M / i + i) % 2 == 0 && (M / i - i) % 2 == 0) {
            i128 x = (M / i + i) / 2; 
            i128 y = (M / i - i) / 2; 
            if((x * x  + y * y) % 2 == 0) {
                ans += (x * x + y * y) / 2;
            }
        }
    }
    string s;
    while(ans) {
        s.push_back('0' + ans % 10);
        ans /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
