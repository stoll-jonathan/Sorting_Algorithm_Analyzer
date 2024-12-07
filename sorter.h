#ifndef SORTER
#define SORTER

class Sorter {
    private:
        unsigned long swaps;
        unsigned long comparisons;
        unsigned int executionTime; // Measured in microseconds
        void mergeSort(int arr[], const int begin, const int end);
        void merge(int arr[], int const left, int const mid, int const right);
    public:
        unsigned long getSwaps();
        unsigned long getComparisons();
        unsigned int getExecutionTime();
        void insertion(int arr[], const int size);
        void bubble(int arr[], const int size);
        void merge(int arr[], const int size);
};

#include "sorter.cpp"
#endif