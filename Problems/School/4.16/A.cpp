#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

bool ck(int x) {
    string s = to_string(x);
    string t = s;
    reverse(s.begin(), s.end());
    return s == t;
}
void solve() { 
    int n;
    cin >> n;
    if(ck(n)) {
        cout << "Yes\n";
    }else{
        cout << "No\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
