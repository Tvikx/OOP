#include "circularBuffer.hpp"

int main()
{
    CircularBuffer<int> a(4);
    CircularBuffer<int> b(a);
    b.push_back(3);
    std::cout << b.size() << b.reserve();
    return 0;
}