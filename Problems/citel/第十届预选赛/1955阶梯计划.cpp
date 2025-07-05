#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int, int>;

//https://citel.bjtu.edu.cn/acm/problem/1955
/*
    区间覆盖 + 贪心 ———— 从左到右贪心
    由于对于每个pos[i], 引爆总是更优, 因此计算出一个合法子序列, 满足区间连续相交即可
*/
void solve(){
    int n;
    cin >> n;
    std::vector<PII> pos(n);
    for(int i = 0; i < n; i++){
        cin >> pos[i].first >> pos[i].second;
    }
    int m;
    cin >> m;
    vector<int> q(m);
    for(int i = 0; i < m; i++){
        cin >> q[i];
    }

    int maxPos = 0;
    for(int i = 0; i < n; i++){
        if(maxPos >= pos[i].first){
            maxPos += pos[i].second;
        }
        else{
            break;
        }
    }
    for(int i = 0; i < m; i++){
        if(q[i] <= maxPos){
            cout << "Yes\n";
        }
        else{
            cout << "No\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
