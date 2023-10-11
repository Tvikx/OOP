#include "circularBuffer.hpp"

int main()
{
    CircularBuffer<int> a(4, 1);
    for (int i = 0; i < 4; i++)
    {
        std::cout << a[i];
    }
    a.back() = 4;
    a.front() = 5;
    for (int i = 0; i < 4; i++)
    {
        std::cout << a[i];
    }
    
    return 0;
}