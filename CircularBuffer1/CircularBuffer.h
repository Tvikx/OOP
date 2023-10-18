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
	CircularBuffer()
	{
		buffer = nullptr;
		head = -1;
		tail = -1;
		sz = 0;
		cap = -1;
	}
	~CircularBuffer()
	{
		free(buffer);
	}
	CircularBuffer(const CircularBuffer& cb)
	{
		this = cb;
	}
	//������������ ����� �������� �������.
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
	//������������ ����� �������� �������, ������� ��������� ��� ��������� elem.
	CircularBuffer(int capacity, const value_type& elem)
	{
		if (capacity < 0)
			std::cerr << "invalid buffer capacity" << std::endl;
		buffer = new value_type[capacity];
		head = 0;
		tail = capacity - 1;
		sz = capacity;
		cap = capacity;
		for (int i = 0; i < capacity; i++)
			buffer[i] = elem;
	}

	//������ �� �������. �� ��������� ������������ �������.
	value_type& operator[](int i)
	{
		return buffer[mod(head + i, cap)];
	}
	const value_type& operator[](int i) const
	{
		return const_cast<const value_type&>(buffer[mod(head + i, cap)]);
	}

	//������ �� �������. ������ ������� ���������� � ������ ��������� �������.
	value_type& at(int i)
	{
		i = mod(head + i, cap);
		if ((i >= tail || i < head) && (this->reserve() != 0))
			throw "not ur mem";
		return buffer[i];
	}
	const value_type& at(int i) const;

	value_type& front() //������ �� ������ �������.
	{
		if (this->empty())
			throw "can't get front element because buffer is empty\n";
		return buffer[head];
	}
	value_type& back()  //������ �� ��������� �������.
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

	//������������ - �������� ��������� ����� ���, ��� ��� ������ �������
	//������������ � ������ �������������� ������. ���������� ��������� 
	//�� ������ �������.
	value_type* linearize()
	{
		while (head != 0)
			this->left_shift();

		return buffer;
	}
	//���������, �������� �� ����� ���������������.
	bool is_linearized() const
	{
		if (head == -1 || tail == -1)
			throw "buffer wasn't defined";
		if (head == 0)
			return true;
		else
			return false;
	}

	//�������� ����� ���, ��� �� �������� ������� �������� ������� 
	//� �������� new_begin.
	void rotate(int new_begin)
	{
		value_type check = this->at(new_begin);
		if (new_begin == 0)
			return void();
		head = mod(head + new_begin, cap);
		tail = mod(tail + new_begin, cap);
	}
	//���������� ���������, ���������� � ������.
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
	//true, ���� size() == capacity().
	bool full() const
	{
		if (sz == cap)
			return true;
		else
			return false;
	}
	//���������� ��������� ����� � ������.
	int reserve() const
	{
		return cap - sz;
	}
	//������� ������
	int capacity() const
	{
		return cap;
	}

	void set_capacity(int new_capacity);
	//�������� ������ ������.
	//� ������ ����������, ����� �������� ����������� ��������� item.
	void resize(int new_size, const value_type& item = value_type());
	//�������� ������������.
	CircularBuffer& operator=(const CircularBuffer& cb)
	{
		buffer = cb.buffer;
		head = cb.head;
		tail = cb.tail;
		sz = cb.sz;
		cap = cb.cap;
	}
	//���������� ���������� ������ � ������� cb.
	void swap(CircularBuffer& cb)
	{
		CircularBuffer temp = this;
		this = cb;
		cb = temp;
	}

	//��������� ������� � ����� ������. 
	//���� ������� ������ ������ ����� ��� �������, �� ��������������
	//������ ������� ������ (�.�., ����� �����������). 
	void push_back(const value_type& item = value_type())
	{
		if (head == -1 || tail == -1)
		{
			head = 0;
			tail = 0;
		}
		if (head == tail && this->full())
			head = mod(head + 1, cap);
		buffer[tail] = item;
		tail = mod(tail + 1, cap);
		if (this->reserve() != 0)
			sz++;
	}
	//��������� ����� ������� ����� ������ ��������� ������. 
	//���������� push_back, ����� ���������� ��������� ������� ������.
	void push_front(const value_type& item = value_type())
	{
		if (head == -1 || tail == -1)
		{
			head = 0;
			tail = 0;
		}
		if (this->full() && head == tail - 1)
			tail = mod(tail - 1, cap);
		head = mod(head - 1, cap);
		buffer[head] = item;
		if (this->reserve() != 0)
			sz++;
	}
	//������� ��������� ������� ������.
	void pop_back()
	{
		if (this->empty())
			throw "buffer is empty";
		tail = mod(tail - 1, cap);
		sz -= 1;
	}
	//������� ������ ������� ������.
	void pop_front()
	{
		if (this->empty())
			throw "buffer is empty";
		head = mod(head + 1, cap);
		sz -= 1;
	}

	//��������� ������� item �� ������� pos. ������� ������ �������� ����������.
	void insert(int pos, const value_type& item = value_type());
	//������� �������� �� ������ � ��������� [first, last).
	void erase(int first, int last);
	//������� �����.
	void clear();

	int mod(int a, int b)
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
};

template<typename value_type>
bool operator==(const CircularBuffer<value_type>& a, const CircularBuffer<value_type>& b);
template<typename value_type>
bool operator!=(const CircularBuffer<value_type>& a, const CircularBuffer<value_type>& b);
