#include <iostream>
#include <chrono>
#include <random>
#include <cstring>
using namespace std;
using namespace std::chrono;

void printArray(const int arr[], int n) {
    for (int k = 0; k < n; k++) {
        cout << arr[k];
        if (k < n - 1) cout << " ";
    }
    cout << endl;
}

// ---------- Bubble Sort ----------
void bubbleSortCount(int arr[], int n, long long &comparisons) {
    comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// ---------- Insertion Sort ----------
void insertionSortCount(int arr[], int n, long long &comparisons) {
    comparisons = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0) {
            comparisons++;
            if (arr[j] > key) { arr[j + 1] = arr[j]; j--; }
            else break;
        }
        arr[j + 1] = key;
    }
}

// ---------- Selection Sort ----------
void selectionSortCount(int arr[], int n, long long &comparisons) {
    comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        if (minIdx != i) {
            int t = arr[i]; arr[i] = arr[minIdx]; arr[minIdx] = t;
        }
    }
}

// ---------- Quick Sort ----------
int partitionCount(int arr[], int low, int high, long long &comparisons) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] <= pivot) {
            i++;
            int t = arr[i]; arr[i] = arr[j]; arr[j] = t;
        }
    }
    int t = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = t;
    return i + 1;
}
void quickSortCount(int arr[], int low, int high, long long &comparisons) {
    if (low < high) {
        int p = partitionCount(arr, low, high, comparisons);
        quickSortCount(arr, low, p - 1, comparisons);
        quickSortCount(arr, p + 1, high, comparisons);
    }
}

// ---------- Merge Sort ----------
void mergeCount(int arr[], int low, int mid, int high, long long &comparisons) {
    int n1 = mid - low + 1, n2 = high - mid;
    int *L = new int[n1], *R = new int[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[low + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    delete[] L; delete[] R;
}
void mergeSortCount(int arr[], int low, int high, long long &comparisons) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSortCount(arr, low, mid, comparisons);
        mergeSortCount(arr, mid + 1, high, comparisons);
        mergeCount(arr, low, mid, high, comparisons);
    }
}

// ---------- Heap Sort ----------
void siftDownCount(int arr[], int root, int size, long long &comparisons) {
    while (true) {
        int largest = root, left = 2 * root + 1, right = 2 * root + 2;
        if (left < size) { comparisons++; if (arr[left] > arr[largest]) largest = left; }
        if (right < size) { comparisons++; if (arr[right] > arr[largest]) largest = right; }
        if (largest == root) break;
        int t = arr[root]; arr[root] = arr[largest]; arr[largest] = t;
        root = largest;
    }
}
void heapSortCount(int arr[], int n, long long &comparisons) {
    comparisons = 0;
    for (int i = n / 2 - 1; i >= 0; i--)
        siftDownCount(arr, i, n, comparisons);
    for (int end = n - 1; end >= 1; end--) {
        int t = arr[0]; arr[0] = arr[end]; arr[end] = t;
        siftDownCount(arr, 0, end, comparisons);
    }
}

// ---------- Run all algorithms on one input ----------
void compareAll(const int base[], int n, const string &label) {
    int temp[10000];
    long long cmp;
    double ms;

    cout << "\n--- " << label << " ---" << endl;

    memcpy(temp, base, n * sizeof(int));
    auto t0 = high_resolution_clock::now();
    bubbleSortCount(temp, n, cmp);
    auto t1 = high_resolution_clock::now();
    ms = duration_cast<microseconds>(t1 - t0).count() / 1000.0;
    cout << "Bubble:    comparisons = " << cmp << ", time = " << ms << " ms" << endl;

    memcpy(temp, base, n * sizeof(int));
    t0 = high_resolution_clock::now();
    insertionSortCount(temp, n, cmp);
    t1 = high_resolution_clock::now();
    ms = duration_cast<microseconds>(t1 - t0).count() / 1000.0;
    cout << "Insertion: comparisons = " << cmp << ", time = " << ms << " ms" << endl;

    memcpy(temp, base, n * sizeof(int));
    t0 = high_resolution_clock::now();
    selectionSortCount(temp, n, cmp);
    t1 = high_resolution_clock::now();
    ms = duration_cast<microseconds>(t1 - t0).count() / 1000.0;
    cout << "Selection: comparisons = " << cmp << ", time = " << ms << " ms" << endl;

    memcpy(temp, base, n * sizeof(int));
    cmp = 0;
    t0 = high_resolution_clock::now();
    quickSortCount(temp, 0, n - 1, cmp);
    t1 = high_resolution_clock::now();
    ms = duration_cast<microseconds>(t1 - t0).count() / 1000.0;
    cout << "Quick:     comparisons = " << cmp << ", time = " << ms << " ms" << endl;

    memcpy(temp, base, n * sizeof(int));
    cmp = 0;
    t0 = high_resolution_clock::now();
    mergeSortCount(temp, 0, n - 1, cmp);
    t1 = high_resolution_clock::now();
    ms = duration_cast<microseconds>(t1 - t0).count() / 1000.0;
    cout << "Merge:     comparisons = " << cmp << ", time = " << ms << " ms" << endl;

    memcpy(temp, base, n * sizeof(int));
    t0 = high_resolution_clock::now();
    heapSortCount(temp, n, cmp);
    t1 = high_resolution_clock::now();
    ms = duration_cast<microseconds>(t1 - t0).count() / 1000.0;
    cout << "Heap:      comparisons = " << cmp << ", time = " << ms << " ms" << endl;
}

int main() {
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = 8;
    int sortedA[] = {5, 7, 14, 19, 23, 32, 34, 62};
    int reversedA[] = {62, 34, 32, 23, 19, 14, 7, 5};

    cout << "========== Part 1: Comparisons on fixed inputs ==========" << endl;
    compareAll(A, n, "Original A");
    compareAll(sortedA, n, "Sorted A");
    compareAll(reversedA, n, "Reversed A");

    cout << "\n========== Part 2: Timing on random arrays ==========" << endl;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 100000);

    int sizes[] = {1000, 5000, 10000};
    for (int s : sizes) {
        int *base = new int[s];
        for (int i = 0; i < s; i++) base[i] = dist(gen);
        cout << "\n### Array size = " << s << " ###" << endl;
        compareAll(base, s, "Random size " + to_string(s));
        delete[] base;
    }

    cout << "\n========== Part 3: Verify sorted first 10 elements ==========" << endl;
    int small[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int temp[8];
    memcpy(temp, small, sizeof(small)); bubbleSortCount(temp, 8, *(new long long));
    cout << "Bubble:    "; printArray(temp, 8);
    memcpy(temp, small, sizeof(small)); insertionSortCount(temp, 8, *(new long long));
    cout << "Insertion: "; printArray(temp, 8);
    memcpy(temp, small, sizeof(small)); selectionSortCount(temp, 8, *(new long long));
    cout << "Selection: "; printArray(temp, 8);
    memcpy(temp, small, sizeof(small)); long long c = 0; quickSortCount(temp, 0, 7, c);
    cout << "Quick:     "; printArray(temp, 8);
    memcpy(temp, small, sizeof(small)); c = 0; mergeSortCount(temp, 0, 7, c);
    cout << "Merge:     "; printArray(temp, 8);
    memcpy(temp, small, sizeof(small)); heapSortCount(temp, 8, c);
    cout << "Heap:      "; printArray(temp, 8);
    return 0;
}
