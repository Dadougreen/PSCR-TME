#pragma once

#include <mutex>
#include <condition_variable>

using namespace std;

class Barrier {
    int counter;
    const int MAX;
    mutex m;
    condition_variable cv;

public:
    Barrier(int max) : counter(0), MAX(max) {}

    void done() {
        unique_lock<mutex> l(m);
        counter++;
        if (counter == MAX) {
            cv.notify_all();
        }
    }

    void waitFor() {
        unique_lock<mutex> l(m);
        while (counter != MAX) {
            cv.wait(l);
        }
    }
};


