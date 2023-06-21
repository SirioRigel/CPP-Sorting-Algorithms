#include "pch.h"
#include "framework.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <string.h>

using namespace std;

/// <summary>
/// This algorithm works very well in low size arrays since the time complexity is O(n); however the
/// the worst time complexity can even be O(n^2) as the avarge number of comparison and swaps generally is O(n^2).
/// </summary>
/// <param name="Array of ints"></param>
/// <param name="Size of the array"></param>
void bubbleSort(int* arr, int size) {
    bool swapped;
    do {
        swapped = false;
        for (int i = 1; i <= size - 1; i++) {
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
    } while (swapped == true);
}

/// <summary>
/// The quicksort is a very powerful (and quick!) (yet complicated!) algorithm with an avarage time complexity of O(n log(n))
/// however, given that it works by splitting the data in different "partitions", it may even
/// have a time complexity of O(n^2). This algorithm can be used even with large amount of elements
/// </summary>
/// <param name="Array of ints"></param>
/// <param name="Size of the array"></param>
void quicksort(int* arr, int size) {
    if (size <= 1)
        return;

    int pivot = size - 1;
    int index = 0;
    int* part1; int size1;
    int* part2; int size2;
    for (int i = 1; i < size; i++) {
        if (arr[pivot] > arr[pivot - 1]) {
            swap(arr[pivot], arr[pivot - 1]);
            if (arr[i] > arr[pivot]) {
                swap(arr[i], arr[pivot]);
            }
            pivot--;
        }
        else {
            part1 = quickPartition(pivot, true, size, arr);
            part2 = quickPartition(pivot, false, size, arr);
            size1 = pivot;
            size2 = size - pivot - 1;
            quicksort(part1, size1);
            quicksort(part2, size2);

            for (int j = 0; j < size1; j++) {
                arr[j] = part1[j];
            }
            arr[size1] = arr[pivot];
            for (int j = 0; j < size2; j++) {
                arr[size1 + 1 + j] = part2[j];
            }

            delete[] part1;
            delete[] part2;

            break;
        }
    }
}
/// <summary>
/// Used to create quickSort partitions to be sorted
/// </summary>
/// <param name="max"></param>
/// <param name="right"></param>
/// <param name="size"></param>
/// <param name="arr"></param>
/// <returns></returns>
int* quickPartition(int max, bool right, int size, int* arr) {
    if (right) {
        int* returned = new int[max];
        if (max == 0) {
            return returned;
        }
        for (int i = 0; i < max; i++) {
            returned[i] = arr[i];
        }
        return returned;
    }
    else {
        int* returned = new int[size - max - 1];
        if (size - max - 1 == 0) {
            return returned;
        }
        for (int i = max + 1; i <= size - 1; i++) {
            returned[i - max - 1] = arr[i];
        }
        return returned;
    }
}

/// <summary>
/// The mergeSort is a divide-and-conquer type of algorithm that just like the quickSort it creates
/// partitions of a base array and sorts them individually. Its time complexity is very low at O(n log (n))
/// </summary>
/// <param name="arr"></param>
/// <param name="iIndex"></param>
/// <param name="fIndex"></param>
void mergeSort(int* arr, int iIndex, int fIndex) {
    if (iIndex < fIndex) {
        int midIndex = iIndex + (fIndex - iIndex) / 2;
        mergeSort(arr, iIndex, midIndex);
        mergeSort(arr, midIndex + 1, fIndex);
        merge(arr, iIndex, midIndex, fIndex);
    }
}

void merge(int* arr, int iIndex, int midIndex, int fIndex) {
    int size1 = midIndex - iIndex + 1;
    int size2 = fIndex - midIndex;

    int* leftArr = new int[size1];
    int* rightArr = new int[size2];

    for (int i = 0; i < size1; ++i)
        leftArr[i] = arr[iIndex + i];
    for (int j = 0; j < size2; ++j)
        rightArr[j] = arr[midIndex + 1 + j];

    int i = 0;
    int j = 0;  
    int k = iIndex;

    while (i < size1 && j < size2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            ++i;
        }
        else {
            arr[k] = rightArr[j];
            ++j;
        }
        ++k;
    }

    while (i < size1) {
        arr[k] = leftArr[i];
        ++i;
        ++k;
    }

    while (j < size2) {
        arr[k] = rightArr[j];
        ++j;
        ++k;
    }

    delete[] leftArr;
    delete[] rightArr;
}