#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int mx = 1000000;
    int n;
    cin >> n;
    while(n--) {
        int x;
        cin >> x;
        int c = 0;
        while(x % 2 == 0) {
            c++;
            x /= 2;
        }
        mx = min(mx, c);
    }
    cout << mx << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
