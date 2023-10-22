#pragma once
#include <iostream>

template<typename value_type>
class CircularBuffer {
	value_type* buffer;
	int head;
	int tail;
	int sz;
	int cap;

	static int mod(int a, int b)
	{
		a = a % b;
		if (a >= 0)
			return a;
		else
			return a + b;
	}

	void left_shift()
	{
		value_type tmp = buffer[0];
		for (int i = 0; i < cap - 1; i++)
			buffer[i] = buffer[i + 1];
		buffer[cap - 1] = tmp;
		head = mod(head - 1, cap);
		tail = mod(tail - 1, cap);
	}

public:
	CircularBuffer()
	{
		buffer = nullptr;
		head = 0;
		tail = 0;
		sz = 0;
		cap = 0;
	}
	~CircularBuffer()
	{
		delete[] buffer;
	}
	CircularBuffer(const CircularBuffer& cb)
	{
		buffer = new value_type[cb.capacity()];
		for (int i = 0; i < cb.capacity(); i++)
			buffer[i] = cb.buffer[i];
		head = cb.head;
		tail = mod(cb.tail, cb.cap);
		cap = cb.cap;
		sz = cb.sz;
	}

	explicit CircularBuffer(int capacity)
	{
		if (capacity < 0)
			std::cerr << "invalid buffer capacity" << std::endl;
		buffer = new value_type[capacity];
		head = 0;
		tail = 0;
		sz = 0;
		cap = capacity;
	}

	CircularBuffer(int capacity, const value_type& elem)
	{
		if (capacity < 0)
			throw "invalid buffer capacity";
		buffer = new value_type[capacity];
		head = 0;
		tail = 0;
		sz = capacity;
		cap = capacity;
		for (int i = 0; i < capacity; i++)
			buffer[i] = elem;
	}

	value_type& operator[](int i)
	{
		return buffer[mod(head + i, cap)];
	}
	const value_type& operator[](int i) const
	{
		return const_cast<const value_type&>(buffer[mod(head + i, cap)]);
	}


	value_type& at(int i)
	{
		i = mod(head + i, cap);
		if ((i >= tail && i < head) && (this->reserve() != 0))
			throw "not ur mem";
		return buffer[i];
	}
	const value_type& at(int i) const
	{
		i = mod(head + i, cap);
		if ((i >= tail && i < head) && (this->reserve() != 0))
			throw "not ur mem";
		return const_cast<const value_type&>(buffer[i]);
	}

	value_type& front()
	{
		if (this->empty())
			throw "can't get front element because buffer is empty\n";
		return buffer[head];
	}
	value_type& back()
	{
		if (this->empty())
			throw "can't get back element because buffer is empty\n";
		return buffer[mod(tail - 1, cap)];
	}
	const value_type& front() const
	{
		if (this->empty())
			throw "can't get front element because buffer is empty\n";
		const_cast<const value_type&>(buffer[head]);
	}
	const value_type& back() const
	{
		if (this->empty())
			throw "can't get back element because buffer is empty\n";
		const_cast<const value_type&>(buffer[mod(tail - 1, cap)]);
	}


	value_type* linearize()
	{
		if (is_linearized())
			return buffer;

		while (head != 0)
			this->left_shift();

		return buffer;
	}

	bool is_linearized() const
	{
		if (buffer == nullptr)
			throw "buffer wasn't defined";
		if (head == 0)
			return true;
		else
			return false;
	}


	void rotate(int new_begin)
	{
		value_type check = this->at(new_begin);
		if (new_begin == 0)
			return void();
		head = mod(head + new_begin, cap);
		tail = mod(tail + new_begin, cap);
	}

	int size() const
	{
		return sz;
	}
	bool empty() const
	{
		if (sz == 0)
			return true;
		else
			return false;
	}

	bool full() const
	{
		if (sz == cap)
			return true;
		else
			return false;
	}

	int reserve() const
	{
		return cap - sz;
	}

	int capacity() const
	{
		return cap;
	}

	void set_capacity(int new_capacity)
	{
		if (new_capacity == cap)
			return;

		value_type* temp = new value_type[new_capacity];
		buffer = linearize();

		if (new_capacity > sz)
		{
			memcpy(temp, buffer, sizeof(value_type) * sz);
			tail = sz;
		}
		else
		{
			for (int i = 0; i < new_capacity; i++)
				temp[i] = buffer[i];
			tail = 0;
			sz = new_capacity;
		}

		delete[] buffer;
		buffer = temp;
		cap = new_capacity;
	}

	void resize(int new_size, const value_type& item = value_type())
	{
		this->set_capacity(new_size);
		if (new_size > sz)
		{
			for (int i = sz; i < new_size; i++)
				buffer[i] = item;
			tail = 0;
			sz = new_size;
		}
	}

	CircularBuffer& operator=(const CircularBuffer& cb)
	{
		if (this->buffer == nullptr) {
			buffer = new value_type[cb.capacity()];
			cap = cb.capacity();
		}
		else
			this->set_capacity(cb.capacity());
		head = cb.head;
		tail = cb.tail;
		sz = cb.sz;

		for (int i = 0; i < cb.capacity(); i++)
			buffer[i] = cb.buffer[i];

		return *this;
	}

	void swap(CircularBuffer& cb)
	{
		CircularBuffer temp = cb;
		if (cb.buffer == nullptr) {
			cb.buffer = new value_type[this->capacity()];
			cb.cap = this->capacity();
		}
		else
			cb.set_capacity(this->capacity());
		cb.head = head;
		cb.tail = tail;
		cb.sz = sz;

		for (int i = 0; i < this->capacity(); i++)
			cb.buffer[i] = buffer[i];
		
		if (buffer == nullptr) {
			buffer = new value_type[temp.capacity()];
			cap = temp.capacity();
		}
		else
			this->set_capacity(temp.capacity());
		head = temp.head;
		tail = temp.tail;
		sz = temp.sz;

		for (int i = 0; i < temp.capacity(); i++)
			buffer[i] = temp.buffer[i];
	}

	void push_back(const value_type& item = value_type())
	{
		if (head == tail && this->full())
			head = mod(head + 1, cap);
		buffer[tail] = item;
		tail = mod(tail + 1, cap);
		if (this->reserve() != 0)
			sz++;
	}

	void push_front(const value_type& item = value_type())
	{
		if (this->full() && head == mod(tail, cap))
			tail = mod(tail - 1, cap);
		head = mod(head - 1, cap);
		buffer[head] = item;
		if (this->reserve() != 0)
			sz++;
	}

	void pop_back()
	{
		if (this->empty())
			throw "buffer is empty";
		tail = mod(tail - 1, cap);
		sz -= 1;
	}

	void pop_front()
	{
		if (this->empty())
			throw "buffer is empty";
		head = mod(head + 1, cap);
		sz -= 1;
	}


	void insert(int pos, const value_type& item = value_type())
	{
		this->at(pos) = item;
	}

	void erase(int first, int last)
	{
		if (first > last)
			throw "first must be less than last";
		first = mod(first, sz);
		last = mod(last, sz);
		buffer = this->linearize();
		int newSize = sz - (last - first + 1);

		value_type* tmp = new value_type[cap];
		int j = 0;
		for (int i = 0; i < sz; i++)
		{
			if (!(i >= first && i <= last)) {
				tmp[j] = buffer[i];
				j++;
			}
		}
		sz = newSize;
		tail = newSize;
		delete buffer;
		buffer = tmp;
	}

	void clear()
	{
		this->erase(0, sz - 1);
	}

};

template<typename value_type>
bool operator==(const CircularBuffer<value_type>& a, const CircularBuffer<value_type>& b)
{
	if (a.size() != b.size())
		return false;
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] != b[i])
			return false;
	}
	return true;
}
template<typename value_type>
bool operator!=(const CircularBuffer<value_type>& a, const CircularBuffer<value_type>& b)
{
	if (a == b)
		return false;
	else
		return true;
}


