#include<bits/stdc++.h>
using namespace std;
class maxHeap{
private:
	vector<int> heap;
	int parent(int index){
		return (index - 1) / 2;
	}
	int leftChild(int index){
		return 2 * index + 1;
	}
	int rightChild(int index){
		return 2 * index + 2;
	}
	void heapInsert(int index){
		while(index > 0 && heap[parent(index)] < heap[index]){
			swap(heap[parent(index)], heap[index]);
			index = parent(index);
		}
	}
	void heapify(int index, int heapSize){
		while(leftChild(index) < heapSize){
			int largest = leftChild(index);
			int right = rightChild(index);
			if(right < heapSize && heap[right] > heap[largest]){
				largest = right;
			}
			if(heap[index] >= heap[largest]){
				break;
			}
			swap(heap[index], heap[largest]);
			index = largest;
		}
	}
public:
	maxHeap(vector<int>& nums){
		heap = nums;
		int lastNonLeaf = parent(heap.size() - 1);
		for(int i = lastNonLeaf; i >= 0; i--){
			heapify(i, heap.size());
		}
	}
	void heapSort(){
		int heapSize = heap.size();
		for(int i = heapSize - 1; i >= 0; i--){
			swap(heap[0], heap[i]);
			heapify(0, i);
		}
	}
	vector<int> getSortedArray(){
		return heap;
	}
	void printHeap(){
		for(int num : heap){
			cout << num << " ";
		}
		cout << endl;
	}
};
int main()
{
	int n;
	cin >> n;
	vector<int> nums(n);
	for(auto& num : nums){
		cin >> num;
	}
	maxHeap mp(nums);
	mp.printHeap();

	mp.heapSort();
	vector<int> sortedArr = mp.getSortedArray();
	for(auto& num : sortedArr){
		cout << num << " ";
	}
	cout << endl;
	return 0;
}