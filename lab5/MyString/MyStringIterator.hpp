#include <iterator>
#pragma once

template <typename T>
class MyStringIterator
{
private:
	T* ptr;

public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using reference = T&;
	using pointer = T*;
	using difference_type = unsigned long long;

	MyStringIterator(T* ptr)
		: ptr(ptr)
	{
	}

	reference operator*() const 
	{
		return *ptr;
	
	}
	pointer operator->() const
	{
		return ptr;
	}

	MyStringIterator& operator++()
	{
		ptr++;

		return *this;
	}

	MyStringIterator& operator--()
	{
		ptr--;

		return *this;
	}

	MyStringIterator& operator+=(const difference_type offset)
	{
		ptr += offset;

		return *this;
	}

	MyStringIterator& operator-=(const difference_type offset)
	{
		ptr -= offset;

		return *this;
	}

	difference_type operator-(const MyStringIterator& it) const { return this->ptr - it.ptr; }

	MyStringIterator operator+(const difference_type& diff) const { return MyStringIterator(ptr + diff); }
	MyStringIterator operator-(const difference_type& diff) const { return MyStringIterator(ptr - diff); }

	MyStringIterator operator++(int)
	{
		MyStringIterator temp(*this);

		++*this;

		return temp;
	}

	MyStringIterator operator--(int)
	{
		MyStringIterator temp(*this);

		--*this;

		return temp;
	}

	reference operator[](const difference_type& offset) const { return *(*this + offset); }

	bool operator==(const MyStringIterator& it) const { return this->ptr == it.ptr; }
	bool operator!=(const MyStringIterator& it) const { return this->ptr != it.ptr; }
	bool operator<(const MyStringIterator& it) const { return this->ptr < it.ptr; }
	bool operator>(const MyStringIterator& it) const { return this->ptr > it.ptr; }
	bool operator>=(const MyStringIterator& it) const { return !(this->ptr < it.ptr); }
	bool operator<=(const MyStringIterator& it) const { return !(this->ptr > it.ptr); }

	operator MyStringIterator<const T>() const { return MyStringIterator<const T>(ptr); }
};
