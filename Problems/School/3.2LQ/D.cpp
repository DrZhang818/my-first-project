#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


string norm(string &s) {
    int i = 0, n = s.size();
    while(i < n && s[i] == '0') i++;
    return i == n ? "0" : s.substr(i);
}
string add(string &a, string &b) {
    int i = a.size() - 1, j = b.size() - 1, c = 0;
    string res;
    while(i >= 0 || j >= 0 || c) {
        if(i >= 0)  c += a[i--] - '0';
        if(j >= 0)  c += b[j--] - '0';
        res.push_back('0' + c % 10);
        c /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}
string sub(string &a, string &b) {
    int i = a.size() - 1, j = b.size() - 1, c = 0;
    string res;
    while(i >= 0) {
        int t = a[i--] - '0' - c;
        if(j >= 0) t -= b[j--] - '0';
        if(t < 0) t += 10, c = 1;
        else c = 0;
        res.push_back('0' + t);
    }
    reverse(res.begin(), res.end());
    return res;
}
int cmp(string &a, string &b) {
    if(a.size() != b.size()) return a.size() - b.size();
    return a.compare(b); 
}
string add_big(string x, string y) {
    int sx = 1, sy = 1;
    if(x[0] == '-') {
        sx = -1;
        x = x.substr(1);
    }
    if(y[0] == '-') {
        sy = -1;
        y = y.substr(1);
    }
    x = norm(x);
    y = norm(y);
    string res;
    if(sx == sy) {
        res = add(x, y);
        if(sx < 0 && res != "0") {
            res = "-" + res;
        }
    } else {
        if(cmp(x, y) >= 0) {
            res = sub(x, y);
            if(sx < 0 && res != "0") {
                res = "-" + res;
            }
        } else {
            res = sub(y, x);
            if(sy < 0 && res != "0") {
                res = "-" + res;
            }
        }
    }
    return res;
}
void solve() { 
    string tot = "0", cost = "0", inc = "0";
    string s;
    while(cin >> s) {
        tot = add_big(tot, s);
        if(s[0] == '-') cost = add_big(cost, s);
        else inc = add_big(inc, s);
    }
    cout << norm(tot) << "\n" << norm(cost) << "\n" << norm(inc) << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
