#include "pch.h"
#include "StringStack.h"

StringStack::StringStack()
	: m_size(0)
	, m_ptrTop(nullptr)
{
}

StringStack::StringStack(const StringStack& other)
{
	try
	{
		if (other.m_size > 0)
		{
			DfsPush(*this, other.GetTopItem());
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
		StringStack tempStack;
		if (other.m_size > 0)
		{
			DfsPush(tempStack, other.GetTopItem());
		}
		
		*this = std::move(tempStack);
	}

	return *this;
}

StringStack& StringStack::operator=(StringStack&& other) noexcept
{
	if (this != std::addressof(other))
	{
		m_size = other.m_size;
		m_ptrTop = std::move(other.m_ptrTop);

		other.m_size = 0;
	}

	return *this;
}

bool StringStack::IsEmpty() const
{
	if (m_size == 0)
	{
		return true;
	}

	return false;
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
	m_size = 0;
	m_ptrTop = nullptr;
}

StringStack::Item& StringStack::GetTopItem() const
{
	if (IsEmpty())
	{
		throw std::logic_error("Stack is empty");
	}

	return *m_ptrTop.get();
}

void StringStack::DfsPush(StringStack& resultStack, Item& itemPtr) const
{
	if (itemPtr.ptrNext != nullptr)
	{
		DfsPush(resultStack, *itemPtr.ptrNext);
	}

	resultStack.Push(itemPtr.value);
}

