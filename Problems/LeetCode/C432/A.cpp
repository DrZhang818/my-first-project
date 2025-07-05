#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


class Solution {
public:
    vector<int> zigzagTraversal(vector<vector<int>>& grid) {
        bool ok = true;
        vector<int> ans;
        for(int i = 0; i < grid.size(); i++){
            auto &row = grid[i];
            if(i & 1){
                reverse(row.begin(), row.end());
            }
            for(auto x : row){
                if(ok){
                    ans.push_back(x);
                }
                ok = !ok;
            }
        }
        return ans;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    return 0;
}
