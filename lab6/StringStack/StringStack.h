#pragma once
#include "pch.h"

class StringStack
{
	struct Item
	{
		Item(std::string const& v, std::shared_ptr<Item> const& p)
			: value(v)
			, ptrNext(p)
		{
		}

		std::string value;
		std::shared_ptr<Item> ptrNext;
	};


public:
	StringStack();

	StringStack(const StringStack& other);
	StringStack(StringStack&& other) noexcept;

	StringStack& operator=(const StringStack& other);
	StringStack& operator=(StringStack&& other) noexcept;

	bool IsEmpty() const;
	void Pop();
	const std::string& GetTop() const;
	void Push(const std::string& string);
	size_t GetSize() const;
	void Clear();

private:
	Item& GetTopItem() const;
	void DfsPush(StringStack& resultStack, Item& itemPtr) const;

	size_t m_size = 0;
	std::shared_ptr<Item> m_ptrTop;
};
