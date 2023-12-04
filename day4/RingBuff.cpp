#include <iostream>
#include "RingBuff.h"

RingBuff::RingBuff(int size) {
    buffer = new int[size];
    bufferSize = size;
    head = 0;

    // initialize the buffer to 1
    for(int i = 0; i < bufferSize; i++) {
        buffer[i] = 1;
    }
}

RingBuff::~RingBuff() {
    delete[] buffer;
}

void RingBuff::increase_next_n(int n, int val) {
    // increase the next n elements by val
    for(int i = 0; i < n; i++) {
        buffer[(head + i + 1) % bufferSize] += val;
    }
}

int RingBuff::pop_element() {
    // returns the first element and sets it to 1
    int element = buffer[head];
    buffer[head] = 1;
    head = (head + 1) % bufferSize;
    return element;
}

int RingBuff::get_head() {
    return buffer[head];
}