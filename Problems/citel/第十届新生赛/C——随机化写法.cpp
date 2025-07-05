#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://citel.bjtu.edu.cn/acm/problemset/426/problem/C
/*
    随机化算法, 构造题
    翻译题意, 即构造3 * k个数字, 满足任意九个数字的差值(mod 360)的中位数 >= 20
*/
bool check(vector<vector<int>>& nums){
    int n = nums.size();
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            for(int k = j + 1; k < n; k++){
                vector<int> temp(9);
                int p = 0;
                for(int q = 0; q < 3; q++){
                    temp[p++] = nums[i][q];
                    temp[p++] = nums[j][q];
                    temp[p++] = nums[k][q];
                }
                sort(temp.begin(), temp.end());
                int cnt = 0;
                for(int i = 0; i < 9; i++){
                    int diff = (temp[(i + 1) % 9] - temp[i] + 360) % 360;
                    if(diff == 0){
                        cnt = 9;
                        break;
                    }
                    else if(diff < 20) cnt++; 
                }
                if(cnt >= 5) return false;
            }
        }
    }
    return true;
}
void solve(){   
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 359);
    int t;
    cin >> t;
    vector<vector<int>> nums(t, vector<int>(3));
    while(1){
        for(int i = 0; i < t; i++){
            for(int j = 0; j < 3; j++){
                nums[i][j] = dis(gen);
            }
        }
        if(check(nums)){
            break;
        }
    }
    

    for(int i = 0; i < t; i++){
        for(int j = 0; j < 3; j++){
            cout << nums[i][j] << ' ';
        }
        cout << '\n';
    }   
}

//下面是o1优化版本

bool check2(vector<vector<int>>& nums){
    int n = nums.size();
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            for(int k = j + 1; k < n; k++){
                vector<int> temp;
                // 收集三个纸条上的9个角度
                temp.insert(temp.end(), nums[i].begin(), nums[i].end());
                temp.insert(temp.end(), nums[j].begin(), nums[j].end());
                temp.insert(temp.end(), nums[k].begin(), nums[k].end());

                sort(temp.begin(), temp.end());
                vector<int> slices(9);
                for(int idx = 0; idx < 9; idx++){
                    int diff = (temp[(idx + 1) % 9] - temp[idx] + 360) % 360;
                    slices[idx] = diff;
                }
                sort(slices.begin(), slices.end());
                // 中位数的披萨块大小
                int median_slice = slices[4];
                if(median_slice < 20) return false;
            }
        }
    }
    return true;
}

void solve2(){   
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 359);
    int t;
    cin >> t;
    vector<vector<int>> nums(t, vector<int>(3));
    while(true){
        set<int> used_numbers;
        for(int i = 0; i < t; i++){
            for(int j = 0; j < 3; j++){
                int num;
                do{
                    num = dis(gen);
                } while(used_numbers.count(num));
                used_numbers.insert(num);
                nums[i][j] = num;
            }
        }
        if(check(nums)){
            break;
        }
    }

    // 输出结果，按要求格式
    for(int i = 0; i < t; i++){
        for(int j = 0; j < 3; j++){
            cout << nums[i][j] << (j == 2 ? '\n' : ' ');
        }
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    return 0;
}
