#pragma once
#include <iostream>

template<typename value_type>
class CircularBuffer {
	value_type* buffer;
	int head;
	int tail;
	int sz;
	int cap;

public:
	CircularBuffer() // create buffer with size of 10
	{
		buffer = (value_type*)malloc(sizeof(value_type) * 10);
		head = 0;
		tail = 0;
		sz = 0;
		cap = 10;
	}
	~CircularBuffer()
	{
		free(buffer);
	}
	CircularBuffer(const CircularBuffer& cb)
	{
		this = cb;
	}

	explicit CircularBuffer(int capacity)
	{
		buffer = (value_type*)malloc(sizeof(value_type) * capacity);
		head = 0;
		tail = 0;
		sz = 0;
		cap = capacity;
	}

	CircularBuffer(int capacity, const value_type& elem)
	{
		buffer = (value_type*)malloc(sizeof(value_type) * capacity);
		
		for (int i = 0; i < capacity; i++)
			buffer[i] = elem;
		head = 0;
		tail = capacity - 1;
		sz = capacity;
		cap = capacity;
	}

	value_type& operator[](int i)
	{
		int idx;
		idx = (head + i) % cap;                            
		if(idx >= 0)
			return buffer[idx];
		else
			return buffer[idx + cap];  
	}
	const value_type& operator[](int i) const;

	value_type& at(int i);
	const value_type& at(int i) const;

	value_type& front()
	{
		return buffer[head];
	} 
	value_type& back()
	{
		if(this->full() && tail == 0)
			return buffer[cap - 1];
		if(tail == 0)
			return buffer[0];
		return buffer[tail - 1];
	} 
	const value_type& front() const;
	const value_type& back() const;


	value_type* linearize();

	bool is_linearized() const;

	void rotate(int new_begin);

	int size() const;
	bool empty() const;

	bool full() const
	{
		if(cap == sz)
			return true;
		else 
			return false;
	}

	int reserve() const;

	int capacity() const;

	void set_capacity(int new_capacity);

	void resize(int new_size, const value_type& item = value_type());

	CircularBuffer& operator=(const CircularBuffer& cb)
	{
		buffer = cb.buffer;
		head = cb.head;
		tail = cb.tail;
		sz = cb.sz;
		cap = cb.cap;
	}

	void swap(CircularBuffer& cb)
	{
		CircularBuffer<value_type> temp;
		temp = cb;
		cb = this;
		this = temp;
	}


	void push_back(const value_type& item = value_type())
	{
		// if(tail == head)
		// {
		// 	if(head == cap - 1)
		// 		head = 0;
		// 	else
		// 		head++;
		// }
		if(tail == cap - 1)
		{
			buffer[tail] = item;
       		tail %= cap - 1;
			if(sz != cap)
        		sz++;
		}
		else
		{
			buffer[tail] = item;
			tail++;
			if(sz != cap)
        		sz++;
		}
	}

	void push_front(const value_type& item = value_type())
	{
		// if(head == tail)
		// {
		// 	if(tail == 0)
		// 		tail = cap - 1;
		// 	else
		// 		tail--;
		// }
		if(head == 0)
		{
       		head = cap - 1;
			buffer[head] = item;
			if(sz != cap)
        		sz++;
		}
		else
		{
			head--;
			buffer[head] = item;
			if(sz != cap)
        		sz++;
		}
	}

	void pop_back();

	void pop_front();


	void insert(int pos, const value_type& item = value_type());

	void erase(int first, int last);

	void clear();
};

template<typename value_type>
bool operator==(const CircularBuffer<value_type>& a, const CircularBuffer<value_type>& b);
template<typename value_type>
bool operator!=(const CircularBuffer<value_type> &a, const CircularBuffer<value_type>& b);