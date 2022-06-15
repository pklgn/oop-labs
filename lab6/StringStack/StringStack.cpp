#include "pch.h"
#include "StringStack.h"

StringStack::~StringStack()
{
	Clear();
}

StringStack::StringStack(const StringStack& other)
{
	try
	{
		if (other.m_size > 0)
		{
			DeepCopy(*this, other.GetTopItem());
		}
	}
	catch (...)
	{
		Clear();

		throw;
	}
}

StringStack::StringStack(StringStack&& other) noexcept
	: m_size(0)
	, m_ptrTop(nullptr)
{
	std::swap(m_size, other.m_size);
	std::swap(m_ptrTop, other.m_ptrTop);
}

StringStack& StringStack::operator=(const StringStack& other)
{
	if (this != std::addressof(other))
	{
		auto tempStack = other; 
		
		*this = std::move(tempStack);
	}

	return *this;
}

StringStack& StringStack::operator=(StringStack&& other) noexcept
{
	std::swap(m_size, other.m_size);
	std::swap(m_ptrTop, other.m_ptrTop);

	return *this;
}

bool StringStack::IsEmpty() const
{
	return m_size == 0;
}

void StringStack::Pop()
{
	if (IsEmpty())
	{
		throw std::logic_error("Stack is empty");
	}

	--m_size;
	m_ptrTop = m_ptrTop->ptrNext;
}

const std::string& StringStack::GetTop() const
{
	if (IsEmpty())
	{
		throw std::logic_error("Stack is empty");
	}

	return m_ptrTop->value;
}

void StringStack::Push(const std::string& string)
{
	++m_size;
	m_ptrTop = std::make_shared<Item>(Item(string, m_ptrTop));
}

size_t StringStack::GetSize() const
{
	return m_size;
}

void StringStack::Clear()
{
	while (!IsEmpty())
	{
		Pop();
	}
}

StringStack::Item& StringStack::GetTopItem() const
{
	if (IsEmpty())
	{
		throw std::logic_error("Stack is empty");
	}

	return *m_ptrTop.get();
}

void StringStack::DeepCopy(StringStack& resultStack, Item& itemPtr) const
{
	if (itemPtr.ptrNext != nullptr)
	{
		DeepCopy(resultStack, *itemPtr.ptrNext);
	}

	resultStack.Push(itemPtr.value);
}
