#pragma once

#include "ThreeWayQuickSort.h"
#include <random>
#include <chrono>
#include <typeinfo>
#include <vector>

#define PROFILING 0
#if PROFILING
#define PROFILE_SCOPE(name) InstrumentationTimer timer##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCTION__)
#else
#define PROFILE_SCOPE(name)
#define PROFILE_FUNCTION()
#endif

using namespace std;

template <typename T, size_t range>

class QuickTester {
public:
    void test(size_t size) {
        PROFILE_FUNCTION();
        T* arr = new T[size];
        fill(arr, size);

        ThreeWayQuickSort<T>::sort(arr, size, 30);

        assert(arr, size);

        print(arr, size);
    }

    //prints out the time it takes to sorts arrays of many sizes
    void benchmark() {
        PROFILE_FUNCTION();
        //printAvgTimes();
        printInstantTimes();
    }

    //prints out coordinates of 20,000 increments
    void graph() {
        PROFILE_FUNCTION();
        for (int i = 0; i <= 10'000'000; i += 20000) {
            cout << "(" << i << ", " << testArray(i) << ")" << endl;
        }
    }

    /*void insertionCutoff() {
        PROFILE_FUNCTION();
        vector<tuple<int, long double>> vec(100);
        for (int i = 1; i <= 200; i += 2) {
            vec.push_back((i, determineAvgTimes(100'000, i)));
        }
    }*/

private:
    void printInstantTimes() {
        PROFILE_FUNCTION();
        //long time1 = testArray(1'000);
        //long time2 = testArray(10'000);
        //long time3 = testArray(100'000);
        //long time4 = testArray(1'000'000);
        //long time5 = testArray(10'000'000);
        //long time6 = testArray(100'000'000);
        long time7 = testArray(1'000'000'000, 30);

        //cout << "1,000 " << getTypeName() << " In " << time1 << " milliseconds." << endl;
        //cout << "10,000 " << getTypeName() << " In " << time2 << " milliseconds." << endl;
        //cout << "100,000 " << getTypeName() << " In " << time3 << " milliseconds." << endl;
        //cout << "1,000,000 " << getTypeName() << " In " << time4 << " milliseconds." << endl;
        //cout << "10,000,000 " << getTypeName() << " In " << time5 << " milliseconds." << endl;
        //cout << "100,000,000 " << getTypeName() << " In " << time6 << " milliseconds." << endl;
        cout << "1,000,000,000 " << getTypeName() << " In " << time7 << " milliseconds." << endl;
    }

    void printAvgTimes() {
        PROFILE_FUNCTION();
        long time1 = determineAvgTimes(1'000);
        long time2 = determineAvgTimes(10'000);
        long time3 = determineAvgTimes(100'000);
        long time4 = determineAvgTimes(1'000'000);
        long time5 = determineAvgTimes(10'000'000);

        cout << "1,000 " << getTypeName() << " In " << time1 << " milliseconds." << endl;
        cout << "10,000 " << getTypeName() << " In " << time2 << " milliseconds." << endl;
        cout << "100,000 " << getTypeName() << " In " << time3 << " milliseconds." << endl;
        cout << "1,000,000 " << getTypeName() << " In " << time4 << " milliseconds." << endl;
        cout << "10,000,000 " << getTypeName() << " In " << time5 << " milliseconds." << endl;
    }

    //runs each sort 5 times and averages it
    long double determineAvgTimes(int size, size_t cutoff) {
        PROFILE_FUNCTION();
        long double time = 0;
        for (int i = 1; i <= 5; i++) {
            time += testArray(size, cutoff);
        }
        return time / 5;
    }

    string getTypeName() {
        PROFILE_FUNCTION();
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0.0, 1.0);
        const auto type = static_cast<T>(dis(gen) * range); // Cast to T if T is not double

        if (typeid(type) == typeid(int)) return "Ints";
        if (typeid(type) == typeid(double)) return "Doubles";

        return typeid(T).name();
    }

    void assert(T* arr, int size) {
        PROFILE_FUNCTION();
        if (!ThreeWayQuickSort<T>::isSorted(arr, size)) {
            cout << " Array not sorted.";
            abort();
        }
    }

    long double testArray(size_t size, size_t cutoff) {
        PROFILE_FUNCTION();
        T* arr = new T[size];
        fill(arr, size);

        auto start = chrono::high_resolution_clock::now();
        ThreeWayQuickSort<T>::sort(arr, size, cutoff);
        auto end = chrono::high_resolution_clock::now();

        long long startTime = std::chrono::time_point_cast<std::chrono::microseconds >(start).time_since_epoch().count();
        long long endTime = std::chrono::time_point_cast<std::chrono::microseconds >(end).time_since_epoch().count();

        auto duration = endTime - startTime;

        delete[] arr;
        return duration / 1000.0;
    }

    void fill(T* arr, size_t size) {
        PROFILE_FUNCTION();
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0.0, 1.0);

        for (size_t i = 0; i < size; ++i) {
            arr[i] = static_cast<T>(dis(gen) * range);
        }
    }

    void print(T* arr, size_t size) {
        PROFILE_FUNCTION();
        for (int i = 0; i < size; i++) {
            cout << i + 1 << ": " << arr[i] << endl;
        }
    }
};
