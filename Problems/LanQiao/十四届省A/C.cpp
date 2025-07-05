#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


string norm(string &s) {
    int i = 0, n = s.size();
    while(i < n && s[i] == '0') i++;
    return i == n ? "0" : s.substr(i);
}
string _add(string &s, string &t) {
    int i = s.size() - 1, j = t.size() - 1, c = 0;
    string res;
    while(i >= 0 || j >= 0 || c > 0) {
        int tmp = c;
        if(i >= 0) tmp += s[i--] - '0';
        if(j >= 0) tmp += t[j--] - '0';
        res += tmp % 10 + '0';
        c = tmp / 10;
    }
    reverse(res.begin(), res.end());
    return norm(res);
}
string _sub(string &s, string &t) {
    int i = s.size() - 1, j = t.size() - 1, c = 0;
    string res;
    while(i >= 0) {
        int tmp = s[i--] - '0' - c;
        if(j >= 0) tmp -= t[j--] - '0';
        if(tmp < 0) {
            tmp += 10;
            c = 1;
        } else {
            c = 0;
        }
        res += tmp + '0';
    }
    reverse(res.begin(), res.end());
    return norm(res);
}
int cmp(string &s, string &t) {
    if(s.size() != t.size()) return s.size() - t.size();
    return s.compare(t);
}
string add(string x, string y) {
    int sx = 1, sy = 1;
    if(x[0] == '-') {
        sx = -1;
        x = x.substr(1);
    } 
    if(y[0] == '-') {
        sy = -1;
        y = y.substr(1);
    }
    norm(x), norm(y);
    string res;
    if(sx == sy) {
        res = _add(x, y);
        if(sx < 0 && res != "0") {
            res = "-" + res;
        }
    } else {
        if(cmp(x, y) > 0) {
            res = _sub(x, y);
            if(sx < 0 && res != "0") {
                res = "-" + res;
            }
        } else {
            res = _sub(y, x);
            if(sy < 0 && res != "0") {
                res = "-" + res;
            }
        }
    }
    return norm(res);
} 
string _mul(string &x, string &y) {
    int i = x.size() - 1, j = y.size() - 1;
    string res = "0";
    for(; i >= 0; i--) {
        string tmp;
        int c = 0;
        for(int p = j; p >= 0; p--) {
            int t = x[i] - '0';
            t *= (y[p] - '0');
            t += c;
            tmp += t % 10 + '0';
            c = t / 10;
        }
        if(c > 0) tmp += c + '0';
        reverse(tmp.begin(), tmp.end());
        norm(tmp);
        for(int j = i; j < x.size() - 1; j++) tmp += "0";
        res = add(res, tmp);
    }
    return norm(res);
}
string mul(string x, string y) {
    int sx = 1, sy = 1;
    if(x[0] == '-') {
        sx = -1;
        x = x.substr(1);
    } 
    if(y[0] == '-') {
        sy = -1;
        y = y.substr(1);
    }
    norm(x), norm(y);
    string res;
    if(sx == sy) {
        res = _mul(x, y);
    } else {
        res = _mul(x, y);
        if(res != "0") {
            res = "-" + res;
        }
    }
    return norm(res);
}
void solve() { 
    string s, t;
    cin >> s >> t;
    string a = mul(s, s);
    string b = mul(t, t);
    b = "-" + b;
    string ans = add(a, b);
    cout << ans << "\n";
}   

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
