#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://citel.bjtu.edu.cn/mlsv3/mod/programming/view.php?a=2726
/*

*/
int cnt = 0;
string s, t;
bool ok = false;
stack<char> stk;
ll call_count = 0;
bool dfs(int i, int j) {
    call_count++;
    if(j == t.size()) {
        if(i == s.size()) return ok = true; 
        return false;
    }
    bool res = false;
    if(i < s.size()) {
        stk.push(s[i]);
        res = (res || dfs(i + 1, j));
        stk.pop();
    }
    if(!stk.empty() && stk.top() == t[j]) {
        stk.pop();
        res = (res || dfs(i, j + 1)); 
        stk.push(t[j]);
    }
    return res;
}
void solve() {
    vector<int> a(128), b(128);
    for(int i = 0; i < s.size(); i++) a[int(s[i])]++, b[int(t[i])]++;
    if(a != b) { cout << "No\n"; return; }
    dfs(0, 0);
    if(ok) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
    // cerr << call_count << "\n";
}

// void gen() {
//     s = t = "";
//     for(int i = 0; i < 100; i++) {
//         s += 'a' + rand() % 26;
//         t += 'a' + rand() % 26;
//     }
// }
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    while(getline(cin,s)) {
        getline(cin,t);
        cnt++;
        cout << "Case " << cnt << ": ";
        ok = false;
        solve();
    }
    // srand(time(0));
    // ll tot = 0, mx = -1;
    // string ms, mt;
    // while(cnt < 1000000) {
    //     if(cnt % 100000 == 0) cerr << cnt / 100000 << "\n";
    //     cnt++;
    //     // cout << "Case " << cnt << ": ";
    //     ok = false;
    //     call_count = 0;
    //     gen();
    //     solve();
    //     tot += call_count;
    //     if(call_count > mx) {
    //         mx = call_count;
    //         ms = s;
    //         mt = t;
    //     }
    // }
    // cout << "average: " << tot / cnt << "\n";
    // cout << "mx: " << mx << "\n";
    // cout << ms << "\n" << mt << "\n";

    return 0;
}