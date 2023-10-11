#include<iostream>

template<class value_type>

class CircularBuffer
{
private:
    value_type* data;
    int sz;
    int cap;
    int head;
    int tail;

public:
    CircularBuffer();
    ~CircularBuffer();
    CircularBuffer(const CircularBuffer &cb);

    // Конструирует буфер заданной ёмкости.
    explicit CircularBuffer(int capacity);
    // Конструирует буфер заданной ёмкости, целиком заполняет его элементом elem.
    CircularBuffer(int capacity, const value_type &elem);

    // Доступ по индексу. Не проверяют правильность индекса.
    value_type &operator[](int i)
    {
        return data[i];
    };
    const value_type &operator[](int i) const
    {
        return const_cast<const value_type&>(data[i]);
    };

    // Доступ по индексу. Методы бросают исключение в случае неверного индекса.
    value_type &at(int i)
    {
        if((head + i < 0) || (head + i > cap))
            throw std::runtime_error("Index_err");
        if(i < 0)
            i = head - i;
        else 
            i = head + i;
        return data[i];
    };
    const value_type &at(int i) const
    {
        if((head + i < 0) || (head + i > cap))
            throw std::runtime_error("Index_err");
        if(i < 0)
            i = head - i;
        else 
            i = head + i;
        return const_cast<const value_type&>(data[i]);
    };

    value_type &front()
    {
        return data[head];
    }; // Ссылка на первый элемент.
    value_type &back()
    {
        return data[tail];
    };  // Ссылка на последний элемент.
    const value_type &front() const
    {
        return const_cast<const value_type&>(data[head]);
    };
    const value_type &back() const
    {
        return const_cast<const value_type&>(data[tail]);
    };

    // Линеаризация - сдвинуть кольцевой буфер так, что его первый элемент
    // переместится в начало аллоцированной памяти. Возвращает указатель
    // на первый элемент.
    value_type *linearize();
    // Проверяет, является ли буфер линеаризованным.
    bool is_linearized() const;
    // Сдвигает буфер так, что по нулевому индексу окажется элемент
    // с индексом new_begin.
    void rotate(int new_begin);
    // Количество элементов, хранящихся в буфере.
    int size() const;
    bool empty() const;
    // true, если size() == capacity().
    bool full() const;
    // Количество свободных ячеек в буфере.
    int reserve() const;
    // ёмкость буфера
    int capacity() const;

    void set_capacity(int new_capacity);
    // Изменяет размер буфера.
    // В случае расширения, новые элементы заполняются элементом item.
    void resize(int new_size, const value_type &item = value_type());
    // Оператор присваивания.
    CircularBuffer &operator=(const CircularBuffer &cb);
    // Обменивает содержимое буфера с буфером cb.
    void swap(CircularBuffer &cb);

    // Добавляет элемент в конец буфера.
    // Если текущий размер буфера равен его ёмкости, то переписывается
    // первый элемент буфера (т.е., буфер закольцован).
    void push_back(const value_type &item = value_type());
    // Добавляет новый элемент перед первым элементом буфера.
    // Аналогично push_back, может переписать последний элемент буфера.
    void push_front(const value_type &item = value_type());
    // удаляет последний элемент буфера.
    void pop_back();
    // удаляет первый элемент буфера.
    void pop_front();

    // Вставляет элемент item по индексу pos. Ёмкость буфера остается неизменной.
    void insert(int pos, const value_type &item = value_type());
    // Удаляет элементы из буфера в интервале [first, last).
    void erase(int first, int last);
    // Очищает буфер.
    void clear();
};

template<class value_type>
CircularBuffer<value_type>::CircularBuffer()
{
    data = NULL;
}

template<class value_type>
CircularBuffer<value_type>::~CircularBuffer()
{
    free(data);
}

template<class value_type>
CircularBuffer<value_type>::CircularBuffer(const CircularBuffer &cb)
{
    data = cb.data;
    head = cb.head;
    tail = cb.tail;
    cap = cb.cap;
    sz = cb.sz;
}

template<class value_type>
CircularBuffer<value_type>::CircularBuffer(int capacity)
{
    data = (value_type*)malloc(capacity * sizeof(value_type));
    head = 0;
    tail = 0;
    cap = capacity;
    sz = 0;
}

template<class value_type>
CircularBuffer<value_type>::CircularBuffer(int capacity, const value_type &elem)
{
    data = (value_type*)malloc(capacity * sizeof(value_type));
    for (int i = 0; i < capacity; i++)
        data[i] = elem;
    
    head = 0;
    tail = capacity - 1;
    cap = capacity;
    sz = capacity;
}

template<class value_type>
int CircularBuffer<value_type>::size() const
{
    return sz;
}

template<class value_type>
bool CircularBuffer<value_type>::empty() const
{
    if(sz == 0) return true;
    else return false;
}

template<class value_type>
bool CircularBuffer<value_type>::full() const
{
    if(sz == cap) return true;
    else return false;
}

template<class value_type>
int CircularBuffer<value_type>::reserve() const
{
    return cap - sz;
}

template<class value_type>
int CircularBuffer<value_type>::capacity() const
{
    return cap;
}

template<class value_type>
void CircularBuffer<value_type>::push_back(const value_type &item)
{
    if(tail >= cap)
        tail %= cap;
    data[tail] = item;
    tail++;
    if(sz == cap)
        continue;
    else
        sz++;
}

template<class value_type>
void push_front(const value_type &item)
{

}



template<class value_type>
bool operator==(const CircularBuffer<value_type> & a, const CircularBuffer<value_type> & b);
template<class value_type>
bool operator!=(const CircularBuffer<value_type> & a, const CircularBuffer<value_type> & b);



