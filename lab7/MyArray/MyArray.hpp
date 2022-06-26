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

	MyArray(MyArray const& other)
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
		
		std::copy(std::begin(other), std::end(other), std::begin(*this));
	}

	MyArray(MyArray&& other) noexcept
		: MyArray()
	{
		m_size = other.m_size;
		m_itemsPtr = std::move(other.m_itemsPtr);

		other.m_size = 0;
	}

	size_t GetSize() const
	{
		return m_size;
	}

	void PushBack(T const& item)
	{
		Resize(m_size + 1);
		m_itemsPtr[m_size - 1] = item;
	}

	void Resize(size_t newSize)
	{
		size_t reachableSize = std::min(m_size, newSize);
		std::unique_ptr<T[]> tempItemsPtr = std::make_unique<T[]>(newSize);

		for (size_t i = 0; i < reachableSize; ++i)
		{
			tempItemsPtr[i] = m_itemsPtr[i];
		}

		m_size = newSize;
		m_itemsPtr = std::move(tempItemsPtr);
	}

	void Clear()
	{
		m_size = 0;
		m_itemsPtr.reset();
	}

	MyArray& operator=(const MyArray& other)
	{
		if (this != std::addressof(other))
		{
			MyArray tempArray;
			try
			{
				for (size_t i = 0; i < other.m_size; ++i)
				{
					tempArray.PushBack(other[i]);
				}
			}
			catch (...)
			{
				Clear();

				throw;
			}

			std::swap(m_size, tempArray.m_size);
			std::swap(m_itemsPtr, tempArray.m_itemsPtr);
		}

		return *this;
	}

	MyArray& operator=(MyArray&& other) noexcept
	{
		if (std::addressof(other) != this)
		{
			m_size = 0;
			m_itemsPtr = nullptr;

			std::swap(m_size, other.m_size);
			std::swap(m_itemsPtr, other.m_itemsPtr);
		}

		return *this;
	}

	const T& operator[](size_t index) const
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range");
		}

		return m_itemsPtr[index];
	}

	T& operator[](size_t index)
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range");
		}

		return m_itemsPtr[index];
	}

	using iterator = MyArrayIterator<T>;
	using const_iterator = MyArrayIterator<const T>;

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