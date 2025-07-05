#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1LL << 32;

int fast_pow(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}
void solve() {
    string s;
    cin >> s;
    int n = s.size();
    unordered_map<char,ll> mp;
    mp['('] = -inf - 1, mp['+'] = -inf - 2, mp['-'] = -inf - 3;
    mp['*'] = -inf - 4, mp['/'] = -inf - 5, mp['^'] = -inf - 6;
    unordered_map<ll,char> back;
    back[-inf - 2] = '+', back[-inf - 3] = '-';
    back[-inf - 4] = '*', back[-inf - 5] = '/', back[-inf - 6] = '^';

    vector<ll> a;
    stack<ll> stk;
    for(int i = 0; i < n; i++) {
        if(isdigit(s[i])) {
            a.push_back(s[i] - '0');
        } else if(s[i] == '(' || s[i] == '^') {
            stk.push(mp[s[i]]);
        } else if(s[i] == ')') {
            while(stk.top() < -inf - 1) {
                a.push_back(stk.top());
                stk.pop();
            }
            stk.pop();
        } else {
            while(!stk.empty() && stk.top() <= mp[s[i]] - (mp[s[i]] % 2)) {
                a.push_back(stk.top());
                stk.pop();
            }
            stk.push(mp[s[i]]);
        }
    }
    while(!stk.empty()) {
        a.push_back(stk.top()); 
        stk.pop();
    }
    while(a.size() > 1) {
        for(int i = 0; i < a.size(); i++) {
            if(a[i] < -inf) {
                cout << back[a[i]];
            } else {
                cout << a[i];
            }
            cout << " \n"[i == a.size() - 1];
        }
        int i = 0;
        while(a[i] >= -inf) i++;
        if(a[i] == -inf - 2) a[i - 2] = a[i - 2] + a[i - 1];
        else if(a[i] == -inf - 3) a[i - 2] = a[i - 2] - a[i - 1];
        else if(a[i] == -inf - 4) a[i - 2] = a[i - 2] * a[i - 1];
        else if(a[i] == -inf - 5) a[i - 2] = a[i - 2] / a[i - 1];
        else a[i - 2] = fast_pow(a[i - 2], a[i - 1]);
        a.erase(a.begin() + i);
        a.erase(a.begin() + i - 1);
    }   
    cout << a[0] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
