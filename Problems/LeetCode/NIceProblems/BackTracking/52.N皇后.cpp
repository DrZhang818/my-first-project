#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://leetcode.cn/problems/n-queens/description/
/*
    题意: 构造所有满足"皇后互相打不到"的合法排列, 并输出方案数
        本质是列排列
    关键在于主副对角线如何记录
        diag1表示副对角线, 其记录方式为 行 + 列
        diag2表示主对角线, 其记录方式为 行 - 列 + n - 1 (这里的n - 1可以视为偏移量) 
    
*/
void solve(){
    int n;
    cin >> n;
    int ans = 0;
    vector<int> queens(n);
    vector<int> col(n), diag1(n * 2 + 1), diag2(n * 2 + 1);
    auto dfs = [&](auto&& dfs, int r){
        if(r == n){
            ans++;
            for(int i = 0; i < n; i++){
                for(int j = 0; j < queens[i]; j++){
                    cout << ".";
                }
                cout << "Q";
                for(int j = queens[i] + 1; j < n; j++){
                    cout << ".";
                }
                cout << "\n";
            }
            cout << "\n";
            return;
        }
        for(int c = 0; c < n; c++){
            int rc = r - c + n - 1;
            if(!col[c] && !diag1[r + c] && !diag2[rc]){
                queens[r] = c;
                col[c] = diag1[r + c] = diag2[rc] = true;
                dfs(dfs, r + 1);
                col[c] = diag1[r + c] = diag2[rc] = false;                                
            }
        }
    };
    dfs(dfs, 0);
    cout << ans << "\n";
}
、
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
  
    
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}