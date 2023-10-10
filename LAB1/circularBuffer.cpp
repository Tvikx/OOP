#include "circularBuffer.hpp"

template<class value_type>
CircularBuffer<value_type>::CircularBuffer()
{
    data = NULL;
    head = NULL;
    tail = NULL;
};

// template<class value_type>
// CircularBuffer<value_type>::~CircularBuffer(){};

// template<class value_type>
// CircularBuffer<value_type>::CircularBuffer(const CircularBuffer &cb)
// {
//     data = cb.data;
//     head = cb.head;
//     tail = cb.tail;
// }