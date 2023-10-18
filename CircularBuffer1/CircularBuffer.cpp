#include "CircularBuffer.h"

int main()
{
	CircularBuffer<int> a(10);
	//std::cout << a.front() << ' ' << a.back();
	//int b = a[4];
	//int* g;
	//for (int i = 0; i < 1000; i++)
	//	a.push_front(1);
	//	a.push_back(5);
	//	a.push_front(3);
	//for (int i = 0; i < 5; i++)
	//	a.pop_front();
	//std::cout << a.size() << std::endl;
	//for (int i = 0; i < a.size(); i++)
	//	std::cout << a[i] << std::endl;
	//std::cout << a.front() << ' ' << a.back() << std::endl;
	//if (a.is_linearized())
	//	std::cout << "ok";
	//else
	//{
	//	std::cout << "not ok" << std::endl;
	//	g = a.linearize();
	//	if (a.is_linearized())
	//		std::cout << "ok" << std::endl;
	//	for (int i = 0; i < a.size(); i++)
	//		std::cout << a[i] << std::endl;

	//	for (int i = 0; i < a.size(); i++)
	//		std::cout << g[i] << std::endl;
	//}
	//
	//std::cout << a.at(0);

	for (int i = 0; i < 1000; i++)
		a.push_back(i);

	for (int i = 0; i < a.size(); i++)
		std::cout << a[i] << std::endl;

	a.rotate(5);

	for (int i = 0; i < a.size(); i++)
		std::cout << a[i] << std::endl;







	return 0;
}