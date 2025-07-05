#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://citel.bjtu.edu.cn/acm/problem/2027
/*
    数论
    处理模运算即可
*/
void solve(){
    int n;
    string p;
    cin >> n >> p;
    int sum = 0, back;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        sum = (sum + s.back() - '0') % 2;
        if(i == n - 1){
            back = (s.back() - '0') % 2 == 0;
        }
    }
    int flag = (p.back() - '0') % 2;
    if(flag == 0 && back || flag == 1 && sum == 0){
        cout << "even\n";
    }
    else{
        cout << "odd\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}