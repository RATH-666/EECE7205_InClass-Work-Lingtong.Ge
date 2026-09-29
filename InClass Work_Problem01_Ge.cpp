#include <iostream>
using namespace std;

void printArray(const int arr[], int n) {
    for (int k = 0; k < n; k++) {
        cout << arr[k];
        if (k < n - 1) cout << " ";
    }
    cout << endl;
}

void bubbleSort(int arr[], int n, int &passes, int &comparisons, int &swaps) {
    passes = 0; comparisons = 0; swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swaps++;
                swapped = true;
            }
        }
        passes++;
        cout << "Pass " << passes << ": ";
        printArray(arr, n);
        if (!swapped) break; 
    }
}

int main() {
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int passes, comparisons, swaps;

    cout << "=== Run 1: original array A ===" << endl;
    cout << "Original: "; printArray(A, n);
    bubbleSort(A, n, passes, comparisons, swaps);
    cout << "Sorted: "; printArray(A, n);
    cout << "Passes: " << passes << " Comparisons: " << comparisons
         << " Swaps: " << swaps << endl;

    int B[] = {5, 7, 14, 19, 23, 32, 34, 62};
    cout << "\n=== Run 2: already sorted copy of A ===" << endl;
    cout << "Original: "; printArray(B, n);
    bubbleSort(B, n, passes, comparisons, swaps);
    cout << "Sorted: "; printArray(B, n);
    cout << "Passes: " << passes << " Comparisons: " << comparisons
         << " Swaps: " << swaps << endl;
    return 0;
}
