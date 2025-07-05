#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    ll a, b;
    cin >> a >> b;
    if(a * b <= 0) {
        cout << "Zero\n";
        return ;
    }   
    if(a > 0) {
        cout << "Positive\n";
        return;
    }
    ll cnt = b - a + 1;
    if(cnt & 1) {
        cout << "Negative\n";
    } else {
        cout << "Positive\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
