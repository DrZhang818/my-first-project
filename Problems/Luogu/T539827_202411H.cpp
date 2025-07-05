#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;


void solve(){
    int m, n;
    cin >> m >> n;
    vector<string> grid(m);
    for(auto& row : grid){
        cin >> row;
    }
    for(auto& row : grid){
        auto it = row.find('H');
        if(it != string::npos){
            int l = 0, r = n - 1;
            int i = l;
            while(i <= r){
                if(row[i] == 'A'){
                    swap(row[i], row[l]);
                    i++;
                    l++;
                }
                else if(row[i] == 'B'){
                    swap(row[i], row[r]);
                    r--;
                }else{
                    i++;
                }
            }
        }
        else{
            int cntA = count(row.begin(), row.end(), 'A');
            int cntB = count(row.begin(), row.end(), 'B');
            if(cntA > cntB){
                for(int i = n - 1; i >= 0; i--){
                    if(cntA > 0){
                        row[i] = 'A';
                        cntA--;
                    }else{
                        row[i] = '#';
                    }
                }
            }else if(cntA < cntB){
                for(int i = 0; i < n; i++){
                    if(cntB > 0){
                        row[i] = 'B';
                        cntB--;
                    }else{
                        row[i] = '#';
                    }
                }
            }else{
                for(int i = 0; i < n; i++){
                    row[i] = '#';
                }
            }
        }
    }
    for(int c = 0; c < n; c++){
        int cnt = 0;
        int l = 0, r = 1;
        for(; r < m; r++){
            if(grid[r][c] != '#' && grid[r][c] != 'H' && grid[r][c] == grid[l][c]){
                grid[r][c] = '#';
                cnt++;
            }else{
                if(cnt > 0){
                    grid[l][c] = '#';
                }
                l = r;
                cnt = 0;
            }
        }
        if(cnt > 0){
            grid[l][c] = '#';
        }
    }
    for(auto& s : grid){
        cout << s << endl;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}