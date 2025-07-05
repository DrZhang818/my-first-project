#include <bits/stdc++.h>
using namespace std;

struct randomGenerator{
    randomGenerator(){
        srand(static_cast<unsigned int>(time(nullptr)));
    }   
    int getRandomIndex(int low, int high){
        return low + rand() % (high - low + 1);
    }
} rng;

void Partition(vector<int>& nums, int low, int high, int& lt, int& gt){
    int pivotIndex = rng.getRandomIndex(low, high);
    swap(nums[low], nums[pivotIndex]);
    int pivot = nums[low];

    lt = low;
    gt = high;
    int i = low;

    while(i <= gt){
        if(nums[i] < pivot){
            swap(nums[i], nums[lt]);
            lt++;
            i++;
        }
        else if(nums[i] > pivot){
            swap(nums[i], nums[gt]);
            gt--;
        }
        else{
            i++;
        }
    }
}

void quickSort(vector<int>& nums, int low, int high){
    if(low >= high){
        return;
    }
    int lt, gt;
    Partition(nums, low, high, lt, gt);
    quickSort(nums, low, lt - 1);
    quickSort(nums, gt + 1, high);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    std::vector<int> nums(n);
    for(auto& num : nums){
        cin >> num;
    }
    quickSort(nums, 0, nums.size() - 1);
    for(auto& num : nums){
        cout << num <<' ';
    }
    cout << '\n';
    return 0;
}
