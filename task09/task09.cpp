#include <iostream>
#include <string>
#include <cassert>
using namespace std;

class Time {
private:
    unsigned short _hours;
    unsigned short _minutes;
    unsigned short _seconds;

public:
    Time(unsigned short hours, unsigned short minutes, unsigned short seconds)
        : _hours(hours), _minutes(minutes), _seconds(seconds) {}

    Time& operator++();

    Time operator++(int);

    Time& operator--();

    Time operator--(int);

    bool operator<(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator<=(const Time& other) const;
    bool operator>=(const Time& other) const;
    bool operator==(const Time& other) const;
    bool operator!=(const Time& other) const;

    bool operator!() const;

    void printTime() const;
};



// Prefix 
Time& Time::operator++() {
    ++_seconds;
    if (_seconds == 60) {
        _seconds = 0;
        ++_minutes;
        if (_minutes == 60) {
            _minutes = 0;
            ++_hours;
            if (_hours == 24) {
                _hours = 0;
            }
        }
    }
    return *this;
}

// Postfix 
Time Time::operator++(int) {
    Time temp = *this;
    ++(*this);
    return temp;
}

// Prefix 
Time& Time::operator--() {
    if (_seconds == 0) {
        _seconds = 59;
        if (_minutes == 0) {
            _minutes = 59;
            if (_hours == 0) {
                _hours = 23;
            }
            else {
                --_hours;
            }
        }
        else {
            --_minutes;
        }
    }
    else {
        --_seconds;
    }
    return *this;
}

// Postfix 
Time Time::operator--(int) {
    Time temp = *this;
    --(*this);
    return temp;
}

bool Time::operator<(const Time& other) const {
    if (_hours < other._hours) {
        return true;
    }
    else if (_hours == other._hours) {
        if (_minutes < other._minutes) {
            return true;
        }
        else if (_minutes == other._minutes) {
            return _seconds < other._seconds;
        }
    }
    return false;
}

bool Time::operator>(const Time& other) const {
    return other < *this;
}

bool Time::operator<=(const Time& other) const {
    return !(*this > other);
}

bool Time::operator>=(const Time& other) const {
    return !(*this < other);
}

bool Time::operator==(const Time& other) const {
    return _hours == other._hours && _minutes == other._minutes && _seconds == other._seconds;
}

bool Time::operator!=(const Time& other) const {
    return !(*this == other);
}

bool Time::operator!() const {
    return _hours == 0 && _minutes == 0 && _seconds == 0;
}

void Time::printTime() const {
    cout << _hours << ":" << _minutes << ":" << _seconds << endl;
}

class Vector
{
    size_t _size = 0;
    size_t _capacity = 15;
    int* _array = new int[_capacity];

public:
    Vector() = default;

    Vector(size_t capacity)
    {
        while (_capacity < capacity)
            _capacity += 15;

        if (_array != nullptr)
            delete[] _array;
        _array = new int[_capacity];
    }

    void push_back(int item);
    void push_front(int item);
    void unique();
    void remove_at(size_t index)
    {
        if (index >= _size)
        {
            cout << "Index out of range." << endl;
            return;
        }

        int* new_arr = new int[_size - 1];
        size_t j = 0;
        for (size_t i = 0; i < _size; ++i)
        {
            if (i != index)
                new_arr[j++] = _array[i];
        }

        delete[] _array;
        _array = new_arr;
        _size--;
    }
    void insert_at(size_t index, int item)
    {
        if (index > _size)
        {
            cout << "" << endl;
            return;
        }

        int* new_arr = new int[_size + 1];
        size_t j = 0;
        for (size_t i = 0; i <= _size; ++i)
        {
            if (i == index)
                new_arr[i] = item;
            else
                new_arr[i] = _array[j++];
        }

        delete[] _array;
        _array = new_arr;
        _size++;
    }
    void sort()
    {
        for (size_t i = 0; i < _size - 1; ++i)
        {
            for (size_t j = 0; j < _size - i - 1; ++j)
            {
                if (_array[j] > _array[j + 1])
                {
                    int temp = _array[j];
                    _array[j] = _array[j + 1];
                    _array[j + 1] = temp;
                }
            }
        }
    }
    void pop_back()
    {
        if (_size > 0)
            --_size;
        else
            cout << "List is empty." << endl;
    }
    void pop_front()
    {
        if (_size > 0)
        {
            int* new_arr = new int[_size - 1];
            for (size_t i = 0; i < _size - 1; ++i)
            {
                new_arr[i] = _array[i + 1];
            }
            delete[] _array;
            _array = new_arr;
            --_size;
        }
        else
            cout << "List is empty." << endl;
    }
    int& back() const
    {
        if (_size < 0)
            assert(!"List is empty.");

        return _array[_size - 1];
    }
    int& front() const
    {
        if (_size < 0)
            assert(!"List is empty");

        return _array[0];
    }
    int& at(size_t index)
    {
        if (index >= _size)
            assert(!"Index out of range");
        return _array[index];
    }

    int& operator[](size_t index)
    {
        if (index >= _size)
            assert(!"Index out of range");
        return _array[index];
    }

    const int* data() const
    {
        return _array;
    }

    size_t find(int item)
    {
        for (size_t i = 0; i < _size; ++i)
        {
            if (_array[i] == item)
                return i;
        }
        return -1;
    }

    friend ostream& operator<<(ostream& print, const Vector& list)
    {
        for (size_t i = 0; i < list._size; ++i)
        {
            print << list._array[i] << " ";
        }
        return print;
    }

    ~Vector()
    {
        delete[] _array;
    }
};
void Vector::unique()
{
    if (_size <= 1)
        return;

    int* new_arr = new int[_size];
    new_arr[0] = _array[0];
    size_t newSize = 1;

    for (size_t i = 1; i < _size; ++i)
    {
        if (_array[i] != _array[i - 1])
        {
            new_arr[newSize++] = _array[i];
        }
    }

    delete[] _array;
    _array = new_arr;
    _size = newSize;
}
void Vector::push_front(int item)
{
    int* arr = new int[_size + 1];
    arr[0] = item;
    for (size_t i = 0; i < _size; i++)
    {
        arr[i + 1] = _array[i];
    }
    delete[] _array;
    _array = arr;
    _size++;
}

void Vector::push_back(int item)
{
    if (_size == _capacity)
    {
        _capacity += 15;
        int* new_arr = new int[_capacity];
        for (size_t i = 0; i < _size; ++i)
        {
            new_arr[i] = _array[i];
        }
        delete[] _array;
        _array = new_arr;
    }

    _array[_size++] = item;
}

