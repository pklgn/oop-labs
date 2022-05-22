#include "pch.h"
#include "MyString.h"

MyString::MyString()
	: m_stringPtr(std::make_unique<char[]>(1))
	, m_length(0)
{
}

MyString::MyString(const char* pString)
	: m_length(strlen(pString))
	, m_stringPtr(std::make_unique<char[]>(m_length + 1))
{
	std::strcpy(m_stringPtr.get(), pString);
}

MyString::MyString(const char* pString, size_t length)
	: m_length(length)
	, m_stringPtr(std::make_unique<char[]>(length + 1))
{
	std::memmove(m_stringPtr.get(), pString, length);
}

MyString::MyString(MyString const& other)
	: m_length(other.GetLength())
	, m_stringPtr(std::make_unique<char[]>(other.GetLength() + 1))
{
	memmove(m_stringPtr.get(), other.GetStringData(), m_length);
}

MyString::MyString(MyString&& other)
	: m_length(0)
{
	m_stringPtr = std::move(other.m_stringPtr);
	std::swap(m_length, other.m_length);
}

MyString::MyString(std::string const& stlString)
	: m_length(stlString.size())
	, m_stringPtr(std::make_unique<char[]>(m_length + 1))
{
	memmove(m_stringPtr.get(), &stlString, m_length);
}

size_t MyString::GetLength() const
{
	return m_length;
}

const char* MyString::GetStringData() const
{
	return m_stringPtr.get();
}


