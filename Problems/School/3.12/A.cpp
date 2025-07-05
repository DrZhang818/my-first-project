#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    char a, b;
    cin >> a >> b;
    if(a > b) {
        cout << ">\n";
    } else if(a == b) {
        cout << "=\n";
    } else {
        cout << "<\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
