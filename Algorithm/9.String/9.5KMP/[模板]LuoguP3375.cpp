#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


void getNext(string &s, vector<int> &a) {
    int n = s.size();
    for(int i = 1; i < n; i++) {
        int j = a[i];
        while(j && s[i] != s[j]) j = a[j];
        a[i + 1] = s[i] == s[j] ? j + 1 : 0;
    }
}
void kmp(string &s, string &t, vector<int> &a) {
    int n = s.size(), m = t.size();
    getNext(t, a);
    int j = 0;
    for(int i = 0; i < n; i++) {
        while(j && s[i] != t[j]) j = a[j];
        if(s[i] == t[j]) j++;
        if(j == m) {
            cout << i - m + 2 << "\n";
            j = a[j];
        }
    }
}
void solve() { 
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    vector<int> Next(m + 1);
    kmp(s, t, Next);
    for(int i = 1; i <= m; i++) {
        cout << Next[i] << " \n"[i == m];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
