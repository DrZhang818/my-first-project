#include <bits/stdc++.h>
using namespace std;

int main(){
    int k;
    cin >> k;
    
    // 定义初始的 6 个角度集
    vector<vector<int>> sets;
    sets.push_back({0, 20, 40});
    sets.push_back({60, 80, 100});
    sets.push_back({120, 140, 160});
    sets.push_back({180, 200, 220});
    sets.push_back({240, 260, 280});
    sets.push_back({300, 320, 340});
    
    // 定义额外的角度集，用于 k > 6
    vector<vector<int>> extra_sets = {
        {50, 170, 290},   // set7
        {10, 190, 310},   // set8
        {30, 210, 330},   // set9
        {70, 230, 350}    // set10
    };
    
    // 根据 k 的值，添加额外的角度集
    for(int i = 6; i < k && i < 10; i++){
        sets.push_back(extra_sets[i-6]);
    }
    
    // 输出结果
    for(auto &s : sets){
        cout << s[0] << " " << s[1] << " " << s[2] << "\n";
    }
    
    return 0;
}
