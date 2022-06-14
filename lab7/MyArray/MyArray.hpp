#pragma once
#pragma once
#include "pch.h"
#include "MyArrayIterator.hpp"

template <typename T, size_t SIZE>
class MyArray
{
public:
	MyArray()
		: m_itemsPtr(std::make_unique<T[]>(SIZE))
		, m_size(SIZE)
	{
	}

	template <typename T1, size_t SIZE1>
	MyArray(MyArray<T1, SIZE1> const& other)
		: MyArray()
	{
		try
		{
			Resize(other.m_size);
		}
		catch (...)
		{
			Clear();

			throw;
		}

		for (size_t i = 0; i < other.m_size; ++i)
		{
			m_itemsPtr[i] = static_cast<T const&>(other[i]);
		}
	}

	template <typename T2, size_t SIZE2>
	MyArray(MyArray<T2, SIZE2>&& other) noexcept
		: MyArray()
	{
		try
		{
			Resize(other.m_size);

			for (size_t i = 0; i < other.m_size; ++i)
			{
				m_itemsPtr[i] = static_cast<T const&>(other[i]);
			}

			other.m_size = 0;
			other.m_itemsPtr = nullptr;
		}
		catch (...)
		{
			Clear();
		}
	}

	size_t GetSize() const
	{
		return m_size;
	}

	void PushBack(T const& item)
	{
		Resize(m_size + 1);
		m_itemsPtr[m_size] = item;
	}

	void Resize(size_t size)
	{
		size_t reachableSize = (m_size < size) ? m_size : size; 
		MyArray<T, size> tempArray;

		for (size_t i = 0; i < reachableSize; ++i)
		{
			tempArray[i] = m_itemsPtr[i];
		}

		m_size = 0;
		m_itemsPtr = nullptr;

		std::swap(m_size, tempArray.m_size);
		std::swap(m_itemsPtr, tempArray.m_itemsPtr);
	}

	void Clear()
	{
		Resize(0);
	}

	template <typename T1, size_t SIZE1>
	MyArray<T, SIZE>& operator=(const MyArray<T1, SIZE1>& other)
	{
		if (std::addressof(other) != this)
		{
			size_t const minSize = (SIZE < SIZE1) ? SIZE : SIZE1;
			for (size_t i = 0; i < minSize; ++i)
			{
				m_itemsPtr[i] = static_cast<T const&>(other[i]);
			}
			
			for (size_t i = SIZE1; i < SIZE; ++i)
			{
				m_itemsPtr[i] = T();
			}

			m_size = SIZE1;
		}

		return *this;
	}

	template <typename T2, size_t SIZE2>
	MyArray& operator=(MyArray<T2, SIZE2>&& other) noexcept
	{
		if (std::addressof(other) != this)
		{
			size_t const minSize = (SIZE < SIZE2) ? SIZE : SIZE2;
			for (size_t i = 0; i < minSize; ++i)
			{
				m_itemsPtr[i] = static_cast<T const&>(other[i]);
			}

			for (size_t i = SIZE2; i < SIZE; ++i)
			{
				m_itemsPtr[i] = T();
			}

			m_size = SIZE2;

			other.m_size = 0;
			other.m_itemsPtr = nullptr;
		}

		return *this;
	}

	const char& operator[](size_t index) const
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range");
		}

		return m_itemsPtr[index];
	}

	char& operator[](size_t index)
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range");
		}

		return m_itemsPtr[index];
	}

	using iterator = MyArrayIterator<char>;
	using const_iterator = MyArrayIterator<const char>;

	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	using reverse_iterator = std::reverse_iterator<iterator>;

	iterator begin()
	{
		return iterator(m_itemsPtr.get());
	}

	iterator end()
	{
		return iterator(m_itemsPtr.get() + m_size);
	}

	const_iterator begin() const
	{
		return const_iterator(m_itemsPtr.get());
	}

	const_iterator end() const
	{
		return const_iterator(m_itemsPtr.get() + m_size);
	}

	reverse_iterator rbegin()
	{
		return std::make_reverse_iterator(end());
	}

	reverse_iterator rend()
	{
		return std::make_reverse_iterator(begin());
	}

	const_reverse_iterator rbegin() const
	{
		return std::make_reverse_iterator(end());
	}

	const_reverse_iterator rend() const
	{
		return std::make_reverse_iterator(begin());
	}

private:
	size_t m_size;
	std::unique_ptr<T[]> m_itemsPtr;
};