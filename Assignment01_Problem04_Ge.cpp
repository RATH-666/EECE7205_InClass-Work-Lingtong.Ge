#include <iostream>
using namespace std;

void printArray(const int arr[], int n) {
    for (int k = 0; k < n; k++) {
        cout << arr[k];
        if (k < n - 1) cout << " ";
    }
    cout << endl;
}

void printIndent(int depth) {
    for (int d = 0; d < depth; d++) cout << "  ";
}

int partition(int arr[], int low, int high, int &comparisons, int depth) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
            printIndent(depth);
            cout << "swap i = " << i << ", j = " << j << ": ";
            printArray(arr + low, high - low + 1);
        }
    }
    int temp = arr[i + 1]; 
    arr[i + 1] = arr[high]; 
    arr[high] = temp;
    printIndent(depth);
    cout << "pivot = " << pivot << " placed at index " << (i + 1) << endl;
    return i + 1;
}

void quickSort(int arr[], int low, int high, int &comparisons, int depth) {
    if (low < high) {
        printIndent(depth);
        cout << "Sorting subarray: ";
        printArray(arr + low, high - low + 1);
        int p = partition(arr, low, high, comparisons, depth);
        quickSort(arr, low, p - 1, comparisons, depth + 1);
        quickSort(arr, p + 1, high, comparisons, depth + 1);
    }
}

int main() {
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisons = 0;

    cout << "=== Run 1: original array A ===" << endl;
    cout << "Original: "; printArray(A, n);
    quickSort(A, 0, n - 1, comparisons, 0);
    cout << "Sorted: "; printArray(A, n);
    cout << "Comparisons: " << comparisons << endl;

    // Run 2: already sorted copy
    int B[] = {5, 7, 14, 19, 23, 32, 34, 62};
    comparisons = 0;
    cout << "\n=== Run 2: sorted copy (worst case) ===" << endl;
    cout << "Original: "; printArray(B, n);
    quickSort(B, 0, n - 1, comparisons, 0);
    cout << "Sorted: "; printArray(B, n);
    cout << "Comparisons: " << comparisons << endl;
    return 0;
}
