#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://www.marscode.cn/practice/vkjwp462l6q75q?problem_id=7414004855077584940
void solve(){
    int n, maxSum;
    cin >> n >> maxSum;
    vector<int> nums(n), freq(14), priority(14);
    for(auto& num : nums){
        cin >> num;
        freq[num]++;
    }

    for(int i = 1; i <= 13; i++){
        priority[i] = i == 1 ? 14 : i;
    }

    vector<int> uniques;
    for(int i = 1; i <= 13; i++){
        if(freq[i] > 0){
            uniques.push_back(i);
        }
    }    

    sort(uniques.begin(), uniques.end(), [&](const int& a, const int& b) -> bool{
        return priority[a] > priority[b];
    });
    PII best = {0, 0};
    bool ok = false;
    for(auto a : uniques){
        if(freq[a] < 3) continue;
        for(auto b : uniques){
            if(b == a && freq[b] < 5)   continue;
            else if(freq[b] < 2)        continue;
            if(maxSum < 3 * a + 2 * b)  continue;
            
            best = {a, b};
            ok = true;
            break;
        }
        if(ok){
            break;
        }
    }
    cout << best.first << ' ' << best.second << ' ' << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    return 0;
}
