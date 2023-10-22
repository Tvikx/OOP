#include "CircularBuffer.h"

int main()
{
	CircularBuffer<int> a(1000);

	for (int i = 0; i < a.capacity(); i++)
		a.push_back(3);

	a.erase(4, 999);
	a.push_back(5);
	a.push_front(43);
	for (int i = 0; i < a.size(); i++)
		std::cout << a[i] << ' ';
	a.clear();
	std::cout << std::endl;
	std::cout << a.size();

	//for (int i = 0; i < a.size(); i++)
	//	std::cout << a[i] << ' ';

	//a.resize(40, 7);
	//std::cout << std::endl;
	////a.push_back(10);
	//for (int i = 0; i < a.size(); i++)
	//	std::cout << a[i] << ' ';

	//CircularBuffer<int> b;

	//b = a;


	//std::cout << b.front();

	//std::cout << std::endl;
	//// const CircularBuffer<int> c(a);

	//for (int i = 0; i < b.size(); i++)
	//	std::cout << b[i] << ' ';
	//
	//b.push_back(4);
	//if (a != b)
	//	std::cout << "nice" << std::endl;
	//std::cout << std::endl;
	////a.push_back(10);
	//for (int i = 0; i < b.size(); i++)
	//	std::cout << b[i] << ' ';





	return 0;
}