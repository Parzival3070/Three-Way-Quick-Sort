#pragma once

#define PROFILING 0
#if PROFILING
#define PROFILE_SCOPE(name) InstrumentationTimer timer##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCTION__)
#else
#define PROFILE_SCOPE(name)
#define PROFILE_FUNCTION()
#endif

template <typename T>

//insertion sort implementation
class InsertionSort {
public:
    //sorts a subarray of arr
    static void insertionSort(T* arr, int low, int high) {
        PROFILE_FUNCTION();
        for (int i = low; i <= high; i++) {
            T key = arr[i];
            int previousIndex = i - 1;

            while (previousIndex >= 0 && (arr[previousIndex] > key)) {
                arr[previousIndex + 1] = arr[previousIndex];
                previousIndex = previousIndex - 1;
            }
            arr[previousIndex + 1] = key;
        }
    }
};

