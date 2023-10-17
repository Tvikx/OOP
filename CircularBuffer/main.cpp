#include "CircularBuffer.h"

int main() 
{
	CircularBuffer<int> a(10);


	for(int i = 0; i < 18; i++)
	{
		a.push_back(i + 1);
		std::cout << a.back() << ' ' << a.front() << std::endl;
	}
	a.push_back(11);
	std::cout << a.back() << ' ' << a.front() << std::endl;
	for(int i = 0; i < 10; i++)
	{
		std:: cout << a[i] << ' ';
	}
	return 0;
}