#include "pch.h"

TEST(addTest, ALL) {
	CircularBuffer<int> c(5);
	c.push_back(1); // pushing back first element
	c.push_front(4); // pushing front second element
	EXPECT_EQ(c.back(), 1); // c = {4, 1} check last element eq 1
	EXPECT_EQ(c.front(), 4); // c = {4, 1} check first element eq 4
	c.push_back(5); // 
	EXPECT_EQ(c.back(), 5); // c = {4, 1, 5} check last element eq 5
	EXPECT_EQ(c.size(), 3); // check c size == 3
	EXPECT_EQ(c[1], 1); // check second element == 1
	c.push_back(3); // c = {4, 1, 5, 3}
	c.push_front(5); // c = {5, 4, 1, 5, 3}
	EXPECT_EQ(c.front(), 5);
	EXPECT_EQ(c.back(), 3);
	EXPECT_EQ(c.size(), c.capacity()); // check buffer is full 
	c.push_back(100); // c = {4, 1, 5, 3, 100}
	EXPECT_EQ(c.back(), 100);
	EXPECT_EQ(c.front(), 4);
	c.push_front(10); // c = {10, 4, 1, 5, 3}
	EXPECT_EQ(c.front(), 10);
}

TEST(deleteTest, ALL) {
	CircularBuffer<char> a(10, 'c'); // a = {'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c'}
	CircularBuffer<char> b(a); // init buffer b which is same to a
	EXPECT_TRUE(a.full());
	for (int i = 0; i < a.capacity(); i++) // deleting all buffer elements
		a.pop_back();
	EXPECT_TRUE(a.empty()); // check buffer is empty
	a = b;
	a.clear(); // clearing buffer
	EXPECT_TRUE(a.empty()); // check buffer is empty
	b.push_front('v'); // b = {'v' ... 'c'}
	EXPECT_EQ(b.front(), 'v'); // check v is the front element 
	b.pop_front(); // delete front
	EXPECT_EQ(b.front(), 'c'); // check 'v' deleted
	EXPECT_EQ(b.size(), b.capacity() - 1); // check buffer size is cap - 1
	b.push_back('e');
	EXPECT_EQ(b.back(), 'e'); // check e is the back element 
	b.erase(1, 8); // delete [b[1]; b[8]]
	EXPECT_EQ(b.size(), 2); // b = {'c', 'e'}
	EXPECT_EQ(b.back(), 'e');
	EXPECT_EQ(b.front(), 'c');
}

TEST(memTest, ALL) {
	CircularBuffer<int> a(10, 4); // init buffer with cap = 10
	EXPECT_EQ(a.capacity(), 10);
	a.set_capacity(30); // set new cap = 30
	EXPECT_EQ(a.capacity(), 30); // check that buffer has 30 cap
	EXPECT_EQ(a.size(), 10); // check that we didn't lose memory
	for (int i = 0; i < a.size(); i++)
		EXPECT_EQ(a[i], 4);
	a.push_back(5); // check that we can add elements in buffer
	EXPECT_EQ(a.size(), 11);
	EXPECT_EQ(a.back(), 5);
	a.push_front(2);
	a.push_front(1);
	EXPECT_EQ(a.size(), 13);
	EXPECT_EQ(a.front(), 1);
	EXPECT_EQ(a.at(1), 2);
	ASSERT_ANY_THROW(a.at(23)); // cheks that we can't accsess not defined mem in buffer; a = {1, 2, 4, .. 4}
	a.set_capacity(3); // set new cap = 3;
	EXPECT_EQ(a.capacity(), 3); // checks changes
	EXPECT_EQ(a.size(), 3);

	EXPECT_EQ(a.at(0), 1); // cheks that we didn't lose mem
	EXPECT_EQ(a.at(1), 2);
	EXPECT_EQ(a.at(2), 4);

	a.resize(10, 3); // set new cap = 10, fill 3
	EXPECT_EQ(a.capacity(), 10); // checks changes
	EXPECT_EQ(a.size(), 10);
	
	for (int i = 3; i < a.size(); i++)
		EXPECT_EQ(a.at(i), 3);

	a.push_back(1000); // checks that we can add elements in resized buffer
	EXPECT_EQ(a.back(), 1000);
	a.push_front(12445);
	EXPECT_EQ(a.front(), 12445);

	CircularBuffer<int> b(3);
	b.push_back(1);
	b.push_back(2);
	b.push_back(3);// init b = {1, 2, 3}
	b.rotate(2);
	EXPECT_EQ(b[0], 3); //  checks that b = {3, 1, 2}
	EXPECT_EQ(b[1], 1);
	EXPECT_EQ(b[2], 2);
	
	CircularBuffer<int> c, d;
	c = a;
	d = b;
	b.swap(a);
	EXPECT_EQ(b.size(), 10);
	EXPECT_EQ(a.size(), 3);

	EXPECT_TRUE(b == c);
	EXPECT_TRUE(a == d);
}

TEST(operatorTest, ALL) {
	CircularBuffer<char> a(10, 'v');
	CircularBuffer<char> b(a);
	EXPECT_TRUE(a == b);
	b.push_back(4);
	EXPECT_FALSE(a == b);
	EXPECT_TRUE(a != b);
	b.push_front('v');
	EXPECT_FALSE(a != b);
}