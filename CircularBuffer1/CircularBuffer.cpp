#include "CircularBuffer.h"

int main()
{
	CircularBuffer<int> a(10);

	for (int i = 0; i < a.capacity(); i++)
		a.push_back(20);

	for (int i = 0; i < a.size(); i++)
		std::cout << a[i] << ' ';

	a.resize(40, 7);
	std::cout << std::endl;
	//a.push_back(10);
	for (int i = 0; i < a.size(); i++)
		std::cout << a[i] << ' ';

	CircularBuffer<int> b(a);

	std::cout << std::endl;
	//a.push_back(10);
	for (int i = 0; i < a.size(); i++)
		std::cout << b[i] << ' ';





	return 0;
}