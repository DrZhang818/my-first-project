#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;


//省空间z函数
void z_algorithm(vector<int> &z, const string &s, int idx) {
    int n = s.size();
    z[0] = n - idx;
    for (int i = 1, c = idx, r = idx, len; i + idx < n; i++) {
        len = r > i + idx ? min(r - i - idx, z[i + idx - c]) : 0;
        while (i + idx + len < n && s[i + idx + len] == s[idx + len]) {
            len++;
        }
        if (i + idx + len > r) {
            r = i + idx + len;
            c = i + idx;
        }
        z[i] = len;
    }
}
//求解t从idx2起始的所有子串与s[idx1:]的匹配长度
void e_algorithm(vector<int> &e, const string &s, const string &t, int idx2, int idx1){
    int n = s.size(), m = t.size();
    vector<int> z(n);
    z_algorithm(z, s, idx1);
    for(int i = 0, c = idx2, r = idx2, len; i + idx2 < m; i++){
        len = r > i + idx2 ? min(r - i - idx2, z[i + idx2 - c]) : 0;
        while(i + idx2 + len < m && idx1 + len < n && t[i + idx2 + len] == s[idx1 + len]){
            len++;
        }
        if(i + idx2 + len > r){
            r = i + idx2 + len;
            c = i + idx2;
        }
        e[i] = len;
    }
}
//Z函数: 求解s[0:]和s[i:]的最长公共前缀长度
vector<int> z_array(const string &s){
    int n = s.size();
    vector<int> Z(n, 0);
    for(int i = 1, c = 1, r = 1, len; i < n; i++){
        len = r > i ? min(r - i, Z[i - c]) : 0;
        while(i + len < n && s[i + len] == s[len]){
            len++;
        }
        if(i + len > r){
            r = i + len;
            c = i;
        }
        Z[i] = len;
    }
    return Z;
}
vector<int> e_array(const string &s, const string &t){
    int n = s.size(), m = t.size();
    vector<int> z = z_array(s);
    vector<int> e(m, 0);
    for(int i = 0, c = 0, r = 0, len; i < m; i++){
        len = r > i ? min(r - i, z[i - c]) : 0;
        while(i + len < m && len < n && t[i + len] == s[len]){
            len++;
        }
        if(i + len > r){
            r = i + len;
            c = i;
        }
        e[i] = len;
    }
    return e;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    vector<int> e(m);
    e_algorithm(e, t, s, 1, 1);
    
    for(auto c : e) cout << c << " ";
    cout << "\n";
    
    return 0;  
}