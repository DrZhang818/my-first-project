#include <stdio.h>
#include <stdlib.h>

int a[100005];

void binaryInsertionSort(int *a, int n) {
    for(int i = 2; i <= n; i++) {
        int x = a[i];
        int l = 0, r = i;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            if(a[mid] > x) {
                r = mid;
            } else {
                l = mid;
            }
        }
        for(int j = i - 1; j >= r; j--) {
            a[j + 1] = a[j];
        }
        a[r] = x;
    }
}

void bubbleSort(int *a, int n) {
    for(int i = 1; i <= n; i++) {
        bool tag = false;
        for(int j = 1; j <= n - i; j++) {
            if(a[j] > a[j + 1]) {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
                tag = true;
            }
        }
        if(!tag) {
            break;
        }
    }
}

void quickSort(int *a, int l, int r) {
    if(l >= r) return;
    int i = l, j = r;
    int x = a[l + r >> 1];
    while(i <= j) {
        while(a[i] < x) i++;
        while(a[j] > x) j--;
        if(i <= j) {
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
            i++;
            j--;
        }
    }
    quickSort(a, l, j);
    quickSort(a, i, r);
}

void selectionSort(int *a, int n) {
    for(int i = 1; i <= n; i++) {
        int idx = i;
        for(int j = i + 1; j <= n; j++) {
            if(a[j] < a[idx]) {
                idx = j;
            }
        }
        int t = a[i];
        a[i] = a[idx];
        a[idx] = t;
    }
}

int help[100005];
void mergeSort(int *a, int l, int r) {
    if(l == r) return;
    int mid = l + r >> 1;
    mergeSort(a, l, mid);
    mergeSort(a, mid + 1, r);
    int i = l, j = mid + 1, idx = 0;
    while(i <= mid && j <= r) {
        if(a[i] > a[j]) {
            help[++idx] = a[j++];
        } else {
            help[++idx] = a[i++];
        }
    }
    while(i <= mid) {
        help[++idx] = a[i++];
    }
    while(j <= r) {
        help[++idx] = a[j++];
    }
    for(int x = 1, y = l; x <= idx; x++, y++) {
        a[y] = help[x];
    }
}

void sift(int *a, int n, int i) {
    while(2 * i <= n) {
        int j = i << 1;
        if(j + 1 <= n && a[j + 1] > a[j]) {
            j++;
        }
        if(a[i] >= a[j]) {
            break;
        }
        int t = a[i];
        a[i] = a[j];
        a[j] = t;
        i = j;
    }
}

void heapSort(int *a, int n) {
    for(int i = n >> 1; i >= 1; i--) {
        sift(a, n, i);
    }
    for(int i = n; i > 1; i--) {
        int t = a[1];
        a[1] = a[i];
        a[i] = t;
        sift(a, i - 1, 1);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    // binaryInsertionSort(a, n);
    bubbleSort(a, n);
    // quickSort(a, 1, n);
    // selectionSort(a, n);
    // mergeSort(a, 1, n);
    // heapSort(a, n);
    for(int i = 1; i <= n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

}