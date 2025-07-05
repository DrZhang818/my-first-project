#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n;
    cin >> n;
    string s;
    cin >> s;
    int ans = 0;
    char ch[3] = {'R', 'G', 'B'};
    for(int i = 1; i < n; i++) {
        if(s[i] == s[i - 1]) { 
            ans += 1;
            for(int j = 0; j < 3; j++) {
                if(ch[j] != s[i - 1] && (i + 1 == n || ch[j] != s[i + 1])) {
                    s[i] = ch[j];
                }
            }
        }
    }   
    cout << ans << "\n";
    cout << s << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
