#include "sorter.h"
#include <iostream>
#include <string>

// File management
#include <fstream>

// Random numbers
#include <cstdlib>
#include <time.h>


// Fills array with random numbers from 0 to 1,000,000
void fillWithRand(int arr[], const int size);

// Copies each element from first argument into second argument
void copyArr(const int original[], int copy[], const int size);

// Sorts the array, measures performance, and stores data in a csv file. Then does the same with the sorted array.
void measureSort(const int givenArr[], const int size, const std::string type, const std::string fileName);

// Creates a csv file of the average of each metric for each sort
void compileAverages(const std::string type, const std::string fileName);

int main() {
    srand(time(0));

    // Generate random number arrays
    int arr1[1000];
    int arr2[10000];
    int arr3[100000];
    fillWithRand(arr1, 1000);
    fillWithRand(arr2, 10000);
    fillWithRand(arr3, 100000);

    // Generate csv files measuring sorting performance
    measureSort(arr1, 1000,   "insertion", "csv/Insertion1000.csv");
    measureSort(arr1, 1000,   "bubble",    "csv/Bubble1000.csv");
    measureSort(arr1, 1000,   "merge",     "csv/Merge1000.csv");
    measureSort(arr2, 10000,  "insertion", "csv/Insertion10000.csv");
    measureSort(arr2, 10000,  "bubble",    "csv/Bubble10000.csv");
    measureSort(arr2, 10000,  "merge",     "csv/Merge10000.csv");
    measureSort(arr3, 100000, "insertion", "csv/Insertion100000.csv");
    measureSort(arr3, 100000, "bubble",    "csv/Bubble100000.csv");
    measureSort(arr3, 100000, "merge",     "csv/Merge100000.csv");
    
    return 0;
}

void fillWithRand(int arr[], const int size) {
    for (int i = 0; i < size; i++)
        arr[i] = rand() % (1000000 + 1);
}

void copyArr(const int original[], int copy[], const int size) {
    for (int i = 0; i < size; i++) {
        copy[i] = original[i];
    }
}

void measureSort(const int unsortedArr[], const int size, const std::string type, const std::string fileName) {
    Sorter s;
    std::fstream fout; 
    fout.open(fileName, std::ofstream::out | std::ofstream::trunc);
    
    // Create sorted version of given array
    int sortedArray[size];
    copyArr(unsortedArr, sortedArray, size);
    s.bubble(sortedArray, size);


    // First find the unsorted array data
    fout << "Runtime,Comparisons,Swaps\n"
         << "Unsorted\n";
    for (int i = 0; i < 10; i++) {
        std::cout << "Measuring unsorted " << type << " " << size << " run #" << (i+1) << "\n";

        int arr[size];
        copyArr(unsortedArr, arr, size);

        if (type == "insertion") {
            s.insertion(arr, size);
        }
        else if (type == "bubble") {
            s.bubble(arr, size);
        }
        else if (type == "merge") {
            s.merge(arr, size);
        }

        fout << s.getExecutionTime() << "," << s.getComparisons() << "," << s.getSwaps() << "\n";
    }


    // Then the sorted array
    fout << "Sorted\n";
    for (int i = 0; i < 10; i++) {
        std::cout << "Measuring sorted " << type << " " << size << " run #" << (i+1) << "\n";
        if (type == "insertion") {
            s.insertion(sortedArray, size);
        }
        else if (type == "bubble") {
            s.bubble(sortedArray, size);
        }
        else if (type == "merge") {
            s.merge(sortedArray, size);
        }

        fout << s.getExecutionTime() << "," << s.getComparisons() << "," << s.getSwaps() << "\n";
    }

    fout.close();
}
