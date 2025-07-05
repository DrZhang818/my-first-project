#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
struct info {
    vector<int> son;
    int num;
    bool is_end;
    bool rep;
    info() : son(26), num(0), is_end(false), rep(false) {}
};

class Trie{
private:
    vector<info> t;
    int cnt = 0;
public:
    Trie(int n) : t(n) {}
    void add(string &s) {
        int cur = 0, n = s.size();
        for(int i = 0; i < n; i++) {
            int ch = s[i] - 'a';
            if(t[cur].son[ch] == 0) t[cur].son[ch] = ++cnt;
            cur = t[cur].son[ch];
            t[cur].num += 1;
            if(i == n - 1) t[cur].is_end = true;
        }
    }
    int query(string &s) {
        int cur = 0;
        for(int i = 0; i < s.size(); i++) {
            int ch = s[i] - 'a';
            if(t[cur].son[ch] == 0) return 3;
            cur = t[cur].son[ch];
        }
        if(t[cur].is_end == false || t[cur].num == 0) return 3;
        if(t[cur].rep) return 2;
        t[cur].rep = true;
        return 1;
    }
};
void solve() { 
    int n;
    cin >> n;
    
    Trie a(800000);
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        a.add(s);
    }

    int q;
    cin >> q;
    while(q--) {
        string s;
        cin >> s;
        int res = a.query(s);
        if(res == 1) cout << "OK\n";
        else if(res == 2) cout << "REPEAT\n";
        else cout << "WRONG\n";
    }    
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
