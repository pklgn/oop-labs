#include <iterator>
#pragma once

template <typename T>
class MyArrayIterator
{
private:
	T* ptr;

public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using reference = T&;
	using pointer = T*;
	using difference_type = ptrdiff_t;

	MyArrayIterator(T* ptr)
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

	MyArrayIterator& operator++()
	{
		ptr++;

		return *this;
	}

	MyArrayIterator& operator--()
	{
		ptr--;

		return *this;
	}

	MyArrayIterator& operator+=(const difference_type offset)
	{
		ptr += offset;

		return *this;
	}

	MyArrayIterator& operator-=(const difference_type offset)
	{
		ptr -= offset;

		return *this;
	}

	difference_type operator-(const MyArrayIterator& it) const { return this->ptr - it.ptr; }

	MyArrayIterator operator+(const difference_type& diff) const { return MyArrayIterator(ptr + diff); }
	MyArrayIterator operator-(const difference_type& diff) const { return MyArrayIterator(ptr - diff); }

	MyArrayIterator operator++(int)
	{
		MyArrayIterator temp(*this);

		++*this;

		return temp;
	}

	MyArrayIterator operator--(int)
	{
		MyArrayIterator temp(*this);

		--*this;

		return temp;
	}

	reference operator[](const difference_type& offset) const { return *(*this + offset); }

	bool operator==(const MyArrayIterator& it) const { return this->ptr == it.ptr; }
	bool operator!=(const MyArrayIterator& it) const { return this->ptr != it.ptr; }
	bool operator<(const MyArrayIterator& it) const { return this->ptr < it.ptr; }
	bool operator>(const MyArrayIterator& it) const { return this->ptr > it.ptr; }
	bool operator>=(const MyArrayIterator& it) const { return !(this->ptr < it.ptr); }
	bool operator<=(const MyArrayIterator& it) const { return !(this->ptr > it.ptr); }

	operator MyArrayIterator<const T>() const { return MyArrayIterator<const T>(ptr); }
};