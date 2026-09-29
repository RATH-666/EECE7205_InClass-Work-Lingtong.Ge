#include <iostream>
using namespace std;

void printArray(const int arr[], int n) {
    for (int k = 0; k < n; k++) {
        cout << arr[k];
        if (k < n - 1) cout << " ";
    }
    cout << endl;
}

void merge(int arr[], int low, int mid, int high, int &comparisons, int &finalMerge) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    int *L = new int[n1];
    int *R = new int[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[low + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = low;
    int before = comparisons;
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    if (low == 0 && high == 7) finalMerge = comparisons - before;

    cout << "merged: ";
    printArray(arr + low, high - low + 1);
    delete[] L; delete[] R;
}

void mergeSort(int arr[], int low, int high, int &comparisons, int &finalMerge) {
    if (low < high) {
        cout << "split: ";
        printArray(arr + low, high - low + 1);
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid, comparisons, finalMerge);
        mergeSort(arr, mid + 1, high, comparisons, finalMerge);
        merge(arr, low, mid, high, comparisons, finalMerge);
    }
}

int main() {
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisons = 0, finalMerge = 0;

    cout << "=== Run 1: original array A ===" << endl;
    cout << "Original: "; printArray(A, n);
    mergeSort(A, 0, n - 1, comparisons, finalMerge);
    cout << "Sorted: "; printArray(A, n);
    cout << "Comparisons: " << comparisons << " (final merge: " << finalMerge << ")" << endl;

    int B[] = {5, 7, 14, 19, 23, 32, 34, 62};
    comparisons = 0; finalMerge = 0;
    cout << "\n=== Run 2: sorted copy ===" << endl;
    cout << "Original: "; printArray(B, n);
    mergeSort(B, 0, n - 1, comparisons, finalMerge);
    cout << "Sorted: "; printArray(B, n);
    cout << "Comparisons: " << comparisons << " (final merge: " << finalMerge << ")" << endl;

    int C[] = {62, 34, 32, 23, 19, 14, 7, 5};
    comparisons = 0; finalMerge = 0;
    cout << "\n=== Run 3: reversed copy ===" << endl;
    cout << "Original: "; printArray(C, n);
    mergeSort(C, 0, n - 1, comparisons, finalMerge);
    cout << "Sorted: "; printArray(C, n);
    cout << "Comparisons: " << comparisons << " (final merge: " << finalMerge << ")" << endl;
    return 0;
}
