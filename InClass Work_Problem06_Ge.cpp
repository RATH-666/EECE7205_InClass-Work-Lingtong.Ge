#include <iostream>
using namespace std;

void printArray(const int arr[], int n) {
    for (int k = 0; k < n; k++) {
        cout << arr[k];
        if (k < n - 1) cout << " ";
    }
    cout << endl;
}

void siftDown(int arr[], int root, int size, int &swaps) {
    while (true) {
        int largest = root;
        int left = 2 * root + 1;
        int right = 2 * root + 2;
        if (left < size && arr[left] > arr[largest]) 
            largest = left;
        if (right < size && arr[right] > arr[largest]) 
            largest = right;
        if (largest == root) 
            break;
        int temp = arr[root]; arr[root] = arr[largest]; arr[largest] = temp;
        swaps++;
        root = largest;
    }
}

void heapSort(int arr[], int n, int &swaps) {
    swaps = 0;
    for (int i = n / 2 - 1; i >= 0; i--)
        siftDown(arr, i, n, swaps);
    cout << "Heap: "; printArray(arr, n);

    for (int end = n - 1; end >= 1; end--) {
        int temp = arr[0]; arr[0] = arr[end]; arr[end] = temp;
        swaps++;
        siftDown(arr, 0, end, swaps);
        cout << "end = " << end << " heap: "; printArray(arr, end);
        cout << "        sorted: "; printArray(arr + end, n - end);
    }
}

int main() {
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int swaps;

    cout << "Original: "; printArray(A, n);
    heapSort(A, n, swaps);
    cout << "Sorted: "; printArray(A, n);
    cout << "Swaps in siftDown: " << swaps << endl;
    return 0;
}
