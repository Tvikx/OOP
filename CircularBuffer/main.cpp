#include "CircularBuffer.h"

int main() 
{
	CircularBuffer<int> a(10, 0);
	int b = a[4];
	b = a[100];
	b = a[0];
	b = a[-1];
	b = a[-11];
	a.push_back(4);
	a.push_front(100);
	a.push_front(200);
	// a.push_back(5);
	// a.push_back(6);
	// a.push_back(4);
	// a.push_back(5);
	// a.push_back(6);
	// a.push_back(4);
	// a.push_back(5);
	// a.push_back(6);
	for(int i = 0; i < 10; i++)
		std::cout << a[i] << ' ';
	return 0;
}