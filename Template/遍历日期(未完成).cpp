#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Date{
    int year;
    int month;
    int day;
    Date(int date){
        year = date / 10000;
        month = (date / 100) % 100;
        day = date % 100;
    }
    int toInt() const{
        return year * 10000 + month * 100 + day;
    }
    bool isLeap() const{
        if(year % 400 == 0 || year % 4 == 0 && year % 100 != 0){
            return true;
        }
        return false;
    }
    int getDaysInMonths{
        static const int daysInMonths[12] = 
    }
};

bool isLeap(int year)
void date(int start, int end){

}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> nums(n);
    for(auto& num : nums){
        cin >> num;
    }
    radixSort(nums);
    for(auto& num : nums){
        cout << num << ' ';
    }
    cout << endl;
    return 0;
}
