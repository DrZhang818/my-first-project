#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void countingSort(vector<int>& nums, int n, int exp, vector<int>& help){
    const int BASE = 10;
    vector<int> cnts(BASE, 0);
    //1.统计每个基数的出现次数
    for(int i = 0; i < n; ++i){
        int digit = (nums[i] / exp) % BASE;
        cnts[digit]++;
    }
    //2.计算每个基数的前缀和，确定其在数组中的位置
    for(int i = 1; i < BASE; ++i){
        cnts[i] += cnts[i - 1];
    }
    //3.从后向前遍历，确保排序的稳定性
    for(int i = n - 1; i >= 0; --i){
        int digit = (nums[i] / exp) % BASE;
        help[--cnts[digit]] = nums[i];
    }
    //4.将排序结果复制回原数组
    for(int i = 0; i < n; i++){
        nums[i] = help[i];
    }
}
void radixSort(vector<int>& nums){
    if(nums.empty()) return;
    //1.找到数组中的最小值和最大值
    int min_num = *min_element(nums.begin(), nums.end()); //ranges::min
    int max_num = *max_element(nums.begin(), nums.end()); //ranges::max
    int offset = 0;
    //2.如果存在负数，调整所有元素使其非负
    if(min_num < 0){
        offset = -min_num;
        for(auto& num : nums){
            num += offset;
        }
    }
    //3.更新最大值以反映偏移
    max_num += offset;
    //4.确定最大数的位数
    int numDigits = 0;
    if(max_num == 0){
        numDigits = 1;
    }else{
        while(max_num > 0){
            numDigits++;
            max_num /= 10;
        }
    }
    //5.排序
    int n = nums.size();
    vector<int> help(n, 0);
    for(int exp = 1; numDigits > 0; exp *= 10, numDigits--){
        countingSort(nums, n, exp, help);
    }
    //6.如果有偏移量，恢复原始值
    if(offset){
        for(auto& num : nums) num -= offset;
    }
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
