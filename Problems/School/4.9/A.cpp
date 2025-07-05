#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    if(a + b > c + d) {
        cout << "Left\n"; 
    } else if(a + b < c + d) {
        cout << "Right\n";
    } else {
        cout << "Balanced\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
