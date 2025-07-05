#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


void solve() {
    string x;
    cin >> x;
    int n = x.size();
    string s(n, '0');
    if(x[0] == '1') {
        s[0] = '2';
    }
    else if(x[0] == '2') {
        s[0] = '3';
    }
    else if(x[0] == '3' || x[0] == '4') {
        s[0] = '5';
    }
    else if(x[0] == '5') {
        s[0] = '7';
    }
    else {
        s[0] = '1';
        s[1] = '1';
    }
    cout << s << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}