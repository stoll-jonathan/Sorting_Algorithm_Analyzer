#include "sorter.h"
#include <chrono>

unsigned long Sorter::getSwaps() {
    return swaps;
}

unsigned long Sorter::getComparisons() {
    return comparisons;
}

unsigned int Sorter::getExecutionTime() {
    return executionTime;
}

void Sorter::bubble(int arr[], const int size) {
    swaps = 0;
    comparisons = 0;
    auto start = std::chrono::high_resolution_clock::now();

    // Perform sort
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j < size-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swaps++;
            }
            comparisons++;
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    executionTime = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
}

void Sorter::insertion(int arr[], const int size) {
    swaps = 0;
    comparisons = 0;
    auto start = std::chrono::high_resolution_clock::now();

    // Perform sort
    for (int u = 1; u < size; u++) {
        const int currUnsorted = arr[u];

        int s;
        for (s = u-1; s >= 0; s--) {
            comparisons++;
            
            if (arr[s] > currUnsorted) {
                arr[s+1] = arr[s];
            }
            else
                break;
        }

        if (arr[s+1] != currUnsorted) {
            arr[s+1] = currUnsorted;
            swaps++;
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    executionTime = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
}

// Setup variables and perform merge sort
void Sorter::merge(int arr[], const int size) {
    swaps = 0;
    comparisons = 0;
    auto start = std::chrono::high_resolution_clock::now();

    // Perform sort
    mergeSort(arr, 0, size-1);
    
    auto stop = std::chrono::high_resolution_clock::now();
    executionTime = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
}

// Divide given array into parts and sort those parts recursively
void Sorter::mergeSort(int arr[], const int begin, const int end) {
    if (begin >= end)
        return;
    
    int mid = begin + (end - begin) / 2;

    mergeSort(arr, begin, mid);
    mergeSort(arr, mid+1, end);
    merge(arr, begin, mid, end);
}

// Merge sorted arrays
void Sorter::merge(int arr[], int const left, int const mid, int const right) {
    int const arrOne = mid - left + 1;
    int const arrTwo = right - mid;
 
    // Split given arr into temporary arrays
    auto *leftArr = new int[arrOne];
    auto *rightArr = new int[arrTwo];
 
    for (auto i = 0; i < arrOne; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < arrTwo; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }


    int arrOneIndex = 0;
    int arrTwoIndex = 0;
    int mergedArrIndex = left;
 
    // Merge the temporary arrays into given arr
    while (arrOneIndex < arrOne && arrTwoIndex < arrTwo) {
        if (leftArr[arrOneIndex] <= rightArr[arrTwoIndex]) {
            arr[mergedArrIndex] = leftArr[arrOneIndex];
            arrOneIndex++;
        }
        else {
            arr[mergedArrIndex] = rightArr[arrTwoIndex];
            arrTwoIndex++;
            swaps++;
        }
        mergedArrIndex++;
        comparisons++;
    }
 
    // Insert any left over elements of the temporary arrays
    while (arrOneIndex < arrOne) {
        arr[mergedArrIndex] = leftArr[arrOneIndex];
        arrOneIndex++;
        mergedArrIndex++;
    }
 
    while (arrTwoIndex < arrTwo) {
        arr[mergedArrIndex] = rightArr[arrTwoIndex];
        arrTwoIndex++;
        mergedArrIndex++;
    }


    // Delete the temporary arrays
    delete[] leftArr;
    delete[] rightArr;
}