#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/1399/problem/D
/*
    构造 || 并查集 || 栈

*/
void solve(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> pos(n);
    stack<int> a0, a1;
    int cur = 0;
    for(int i = 0; i < n; i++){
        if(s[i] == '0'){
            a0.push(i);
            if(a1.size() > 0){
                pos[i] = pos[a1.top()];
                a1.pop();
            }else{
                cur++;
                pos[i] = cur;
            }
        }else{
            a1.push(i);
            if(a0.size() > 0){
                pos[i] = pos[a0.top()];
                a0.pop();
            }else{
                cur++;
                pos[i] = cur;
            }
        }
        
    }
    cout << cur << "\n";
    for(auto c : pos){
        cout << c << " ";
    }
    cout << "\n";
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
