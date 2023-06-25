#include "pch.h"
#include "framework.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <string.h>

using namespace std;

/// <summary>
/// The bubble sort algorithm is a simple algorithm that works by checking if every element in the list is 
/// greater than the previous one; as such it works very well in low size arrays with a time complexity of O(n).
///  However given the nature of the algorithm the worst time complexity is O(n^2) as the avarge number of comparison 
/// and swaps generally is O(n^2).
/// </summary>
/// <param name="Array of ints"></param>
/// <param name="Size of the array"></param>
void bubbleSort(int* arr, int size) {
    if (size < 2) return;
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
/// The quicksort is a very powerful (and quick!) algorithm with an avarage time complexity of O(n log(n))
/// however, given that it works by splitting the data in different "partitions", in the worst case scenario
/// has a time complexity of O(n^2). This algorithm can even be used with large amount of elements
/// </summary>
/// <param name="Array of ints"></param>
/// <param name="Size of the array"></param>
void quicksort(int* arr, int size) {
    if (size < 2) return;

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
/// The mergeSort is a divide-and-conquer type of algorithm which, just like the quickSort, creates
/// partitions of a base array and sorts them individually; then it "merges" them together. 
/// Its time complexity is very low at O(n log (n)) but it scales quickly with n.
/// </summary>
/// <param name="Array of ints"></param>
/// <param name="Initial index"></param>
/// <param name="Final index"></param>
void mergeSort(int* arr, int iIndex, int fIndex) {
    if (iIndex < fIndex) {
        int midIndex = iIndex + (fIndex - iIndex) / 2;
        mergeSort(arr, iIndex, midIndex);
        mergeSort(arr, midIndex + 1, fIndex);
        merge(arr, iIndex, midIndex, fIndex);
    }
}

/// <summary>
/// Used to merge the little arrays into the initial array in Merge sort
/// </summary>
/// <param name="arr"></param>
/// <param name="iIndex"></param>
/// <param name="midIndex"></param>
/// <param name="fIndex"></param>
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

/// <summary>
/// The insertion sort is a simple sorting algorithm that compares the adjacent values of an array and inserts their value into
/// its correct place. 
/// Altough it's simple to implement, it has an avarage time complexity of O(n^2) which makes it very slow
/// for large data sets, but still pretty fast compared to other "quadratic" algorithms like bubble sort.
/// </summary>
/// <param name="Array of ints"></param>
/// <param name="Size of the array"></param>
void insertionSort(int* arr, int size) {
    if (size < 2) return;
    for (int i = 1; i < size; i++) {
        int j = i;
        while (j > 0 && arr[j - 1] > arr[j]) {
            swap(arr[j], arr[j - 1]);
            j--;
        }
    }
}

/// <summary>
/// The selection sort is a very slow and inefficient sorting algorithm when it comes to large lists having 
/// an avarage time complexity of O(n^2). It works by dividing the list into two "sub arrays" within the list itself
/// : the first will be the final list, while the second is full of unsorted items.
/// Its major upside is the restriced use of memory compared to other sorting algorithms.
/// </summary>
/// <param name="arr"></param>
/// <param name="size"></param>
void selectionSort(int* arr, int size) {
    if (size < 2) return;
    for (int i = 0; i < size - 1; i++) {
        int jmin = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] > arr[jmin]) {
                jmin = j;
            }
        }
        if (jmin != i) {
            swap(arr[i], arr[jmin]);
        }
    }
}

/// <summary>
/// The shell sort is an interesting algorithm as it is very similar to an insertion sort but it uses "gaps" which are basically
/// integeres that make the element of the unsorted array jump to the beginning of the array itself. The time complexity
/// is pretty difficult to analize but it depends on the gaps used in the sorting algorithm itself. In this I've used Ciura's
/// sequence, which is currently the best known sequence of gaps for shell sort, even if other sequences might work better with very large arrays.
/// </summary>
/// <param name="Array of ints"></param>
/// <param name="Size of the array"></param>
void shellSort(int* arr, int size) {
    if (size < 2) return;
    int gaps[] = { 1750, 701, 301, 132, 57, 23, 10, 4, 1};
    for (int i = 0; i < 9; i++) {
        int gap = gaps[i];
        for (int j = gap; j < size; j++) {
            int temp = arr[j];
            while (j >= gap && (arr[j - gap] > temp)) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

/// <summary>
/// Library sort is an interesting sorting algorithm that works just like an insertion sort; however the main difference
/// between the insertion and this algorithm is that the library leaves spaces before and after a determined value to further
/// introduce another value without having to move every single value (just like a librarian would, hence the name).
/// Its time complexity can be of O(n log n) but it can degenerate quickly in O(n) especially with large arrays
/// </summary>
/// <param name="Array of ints"></param>
/// <param name="Size of array"></param> 
void librarySort(int* arr, int size) {
    int lsize = size * 2;
    int* lib = new int[lsize];

    for (int i = 1; i <= floor(log2(size)); i++) {
        rebalance(lib, 1, pow(2, i - 1));
        int j = pow(2, i - 1);
        while (j < pow(2, i) && j < size) {
            int ins = binarySearch(arr[j], lib, pow(2, i));
            lib[ins] = arr[j];
            j++;
        }
    }

    for (int i = 0; i < size; i++) {
        if (lib[i] != ' ' && lib[i] != '\0') {
            arr[i] = lib[i];
        }
        
    }

    delete[] lib;
}

/// <summary>
/// The rebalance function is used in library sort
/// </summary>
void rebalance(int* lib, int begin, int end) {
    int r = end;
    int w = end * 2;
    while (r >= begin) {
        lib[w] = lib[r];
        lib[w - 1] = 2;
        r--;
        w -= 2;
    }
}

/// <summary>
/// Binary search for library sort
/// </summary>
int binarySearch(int value, int* lib, int size) {

    int low = 0;
    int high = size - 1;

    while (low < high - 1) {
        int mid = low + (high - low) / 2;

        if (lib[mid] == value) {
            return mid;
        }
        else if (lib[mid] < value) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
}

/// <summary>
/// The gnome sort is an interesting sorting algorithm: it's defenetly the least recommended for sorting
/// large arrays as its time complexity is tipically O(n^2). It's the same technique used by a gnome when sorting
/// flower pots: if the one on the right is smaller, it swaps them and goes back swapping until all of the previous
/// are sorted, then it moves on.
/// </summary>
/// <param name="arr"></param>
/// <param name="size"></param>
void gnomeSort(int* arr, int size) {
    int pos = 0;
    while (pos < size) {
        if (pos == 0 || arr[pos] >= arr[pos - 1]) {
            pos++;
        }
        else {
            swap(arr[pos], arr[pos - 1]);
            pos--;
        }
    }
}

/// <summary>
/// The bogo sort, or stupid sort, is a sorting algorithm that works by permutating the initial list of
/// ints and then checking if they are sorted. this is one of the worst sorting algorithms when it comes to 
/// time complexity due to the fact the the avarage TC is O(n*n!).
/// </summary>
/// <param name="arr"></param>
/// <param name="size"></param>
void bogoSort(int* arr, int size) {
    if (size < 2) return;
    while (!sorted(arr, size)) {
        shuffle(arr, size);
    }
}

bool sorted(int* arr, int size) {
    int counter = 0; // until size - 1
    for (int i = 1; i < size; i++) {
        if (arr[i] > arr[i - 1]) {
            counter++;
        }
    }
    if (counter == size - 1) {
        return true;
    }
    else {
        return false;
    }
}

void shuffle(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        int rnd = rand() % size;
        int temp = arr[rnd];
        arr[rnd] = arr[i];
        arr[i] = temp;
    }
}