#pragma once

#include <iostream>
#include "InsertionSort.h"

#define PROFILING 0
#if PROFILING
#define PROFILE_SCOPE(name) InstrumentationTimer timer##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCTION__)
#else
#define PROFILE_SCOPE(name)
#define PROFILE_FUNCTION()
#endif

template <typename T>

class ThreeWayQuickSort {
public:
    static void sort(T* arr, size_t size, size_t cutoff) {
        PROFILE_FUNCTION();
        quickSort(arr, 0, size - 1, cutoff);
    }

    static bool isSorted(T* arr, size_t size) {
        PROFILE_FUNCTION();
        for (int i = 1; i < size; i++) {
            if (less(arr[i], arr[i-1])) {
                std::cout << i;
                return false;
            }
        }

        return true;
    }

private:
    static void quickSort(T* arr, int low, int high, size_t cutoff) {
        PROFILE_FUNCTION();

        //escape point for recursion
        if (high <= low) {
            return;
        }

        //triggers insertion sort at 30 items
        if (high - low <= cutoff) {
            InsertionSort<T>::insertionSort(arr, low, high);
            return;
        }

        int lowPointer = low;
        int i = low + 1;
        int highPointer = high;

        //gets pivot based on different methods
        double pivot = getPivot(arr, low, high, true);

        //partitions the subarray into 3 sections, less than, equal to, and greater than
        while (i <= highPointer) {
            if (arr[i] < pivot) {
                exchange(arr, lowPointer++, i++);
            }
            else if (arr[i] > pivot) {
                exchange(arr, i, highPointer--);
            }
            else {
                i++;
            }
        }

        quickSort(arr, low, lowPointer - 1, cutoff);
        quickSort(arr, highPointer + 1, high, cutoff);
    }

    static double getPivot(T* arr, int low, int high, bool useMedianOfThree) {
        PROFILE_FUNCTION();
        //median of three method
        if (useMedianOfThree) {
            int center = low + (high - low) / 2;
            int pivotIndex = medianOfThree(arr, low, center, high);
            double pivot = arr[pivotIndex];
            exchange(arr, pivotIndex, low); //moves pivot to start of array
            return pivot;
        }
        else { //first element pivot selection
            double pivot = arr[low];
            return pivot;
        }
    }

    static int medianOfThree(T* arr, int a, int b, int c) {
        PROFILE_FUNCTION();
        if (less(arr[a], arr[b])) {
            if (less(arr[b], arr[c])) {
                return b; //a < b < c
            } else if (less(arr[a], arr[c])) {
                return c; //a < c <= b
            } else {
                return a; //c <= a < b
            }
        } else {
            if (less(arr[a], arr[c])) {
                return a; //b <= a < c
            } else if (less(arr[b], arr[c])) {
                return c; //b < c <= a
            } else {
                return b; //c <= b <= a
            }
        }
    }

    static void exchange(T* arr, int i, int j) {
        PROFILE_FUNCTION();
        T temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    static bool less(T v, T w) {
        PROFILE_FUNCTION();
        return v < w;
    }
};
