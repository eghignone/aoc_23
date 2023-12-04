#ifndef RINGBUFF_H
#define RINGBUFF_H


class RingBuff {
public:
    int head;
    RingBuff(int size);
    ~RingBuff();
    void increase_next_n(int n, int val);
    int pop_element();
    int get_head();

private:
    int* buffer;
    int bufferSize;
};

#endif // RINGBUFF_H ///:~
