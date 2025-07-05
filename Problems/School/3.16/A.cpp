#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    string s;
    cin >> s;
    if(s == "Sunny") {
        cout << "Cloudy\n";
    } else if(s == "Cloudy") {
        cout << "Rainy\n";
    } else {
        cout << "Sunny\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
