#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int a, b;
    cin >> a >> b;
    int c = 0, cur = 1;
    while(cur < b) {
        cur = cur - 1 + a;
        c++;
    }
    cout << c << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
