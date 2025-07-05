#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int a, b;
    cin >> a >> b;
    if(a == 1) a += 13;
    if(b == 1) b += 13;
    if(a < b){
        cout << "Bob\n";
    }else if(a == b){
        cout << "Draw\n";
    }else{
        cout << "Alice\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}