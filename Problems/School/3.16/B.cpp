#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    string s;
    cin >> s;
    for(int i = 0; i < s.size(); i++) {
        int j = i + 1;
        if(j % 2 == 1) {
            if(s[i] != 'R' && s[i] != 'U' && s[i] != 'D') {
                cout << "No\n";
                return;
            }
        } else {
            if(s[i] != 'L' && s[i] != 'U' && s[i] != 'D') {
                cout << "No\n";
                return;
            }
        }
    }
    cout << "Yes\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
