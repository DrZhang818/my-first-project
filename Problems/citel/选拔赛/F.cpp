#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

struct stu{
    int id;
    int num;
    int time; 
};
void solve(){
    int n;
    cin >> n;
    vector<stu> stus(n);
    for(int i = 0; i < n; i++){
        cin >> stus[i].id >> stus[i].num >> stus[i].time;
    }
    sort(stus.begin(), stus.end(), [](const stu& a, const stu& b) -> bool{
        if(a.num != b.num){
            return a.num > b.num;
        }
        if(a.time != b.time){
            return a.time < b.time;
        }
        return a.id < b.id;
    });
    for(auto &s : stus){
        cout << s.id << " " << s.num << " " << s.time << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}