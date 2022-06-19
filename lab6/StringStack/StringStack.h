#pragma once
#include "pch.h"

class StringStack
{
public:
	StringStack() = default;

	~StringStack();

	StringStack(const StringStack& other);
	StringStack(StringStack&& other) noexcept;

	StringStack& operator=(const StringStack& other);
	StringStack& operator=(StringStack&& other) noexcept;

	// TODO: перегруппировать операции чтения и записи
	bool IsEmpty() const;
	void Pop();
	const std::string& GetTop() const;
	void Push(const std::string& string);
	size_t GetSize() const;
	void Clear();



private:
	// TODO: unique_ptr
	struct Item
	{
		inline Item(std::string const& value, std::shared_ptr<Item> const& ptr)
			: value(value)
			, ptrNext(ptr)
		{
		}

		std::string value;
		std::shared_ptr<Item> ptrNext;
	};

	Item& GetTopItem() const;
	void DeepCopy(StringStack& resultStack, Item& itemPtr) const;

	size_t m_size = 0;
	std::shared_ptr<Item> m_ptrTop;
};
