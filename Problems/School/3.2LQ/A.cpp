#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    auto check = [&](int x) -> bool {
        return (x % 400 == 0 || x % 100 != 0 && x % 4 == 0);
    };
    int i = 2025;
    ll cur = 0;
    for(;;i++){
        cur += check(i) ? 366 : 365;
        if(cur % 7 == 0) break;
    }
    cout << i;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
