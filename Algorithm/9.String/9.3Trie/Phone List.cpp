#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


struct info {
    int son[10] = {0};
    bool is_end = false;
};
bool add(string &s, vector<info> &trie, int &cnt) {
    int cur = 0;
    bool ok1 = false, ok2 = true;
    for(int i = 0; i < (int)s.size(); i++) {
        int c = s[i] - '0';
        if(trie[cur].son[c] == 0) {
            trie.push_back(info());
            ok2 = false;
            trie[cur].son[c] = ++cnt;
        }
        cur = trie[cur].son[c];
        if(trie[cur].is_end) ok1 = true;
        if(i == (int)s.size() - 1) {
            trie[cur].is_end = true;
        }
    }
    return ok1 || ok2;
}
void solve() { 
    int n;
    cin >> n;
    vector<info> trie;
    int cnt = 0;
    trie.push_back(info());
    bool ok = false;
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if(add(s, trie, cnt)) {
            ok = true;
        }
    }
    if(ok) {
        cout << "NO\n"; 
    } else {
        cout << "YES\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
