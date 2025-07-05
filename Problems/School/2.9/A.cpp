#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    int n, k, x, y;
    cin >> n >> k >> x >> y;
    if(n > k) {
        cout << k * x + (n - k) * y << "\n";
    }else {
        cout << n * x << "\n";
    }
    
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

