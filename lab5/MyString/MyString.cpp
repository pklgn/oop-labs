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

MyString MyString::SubString(size_t start, size_t length) const
{
	if (m_length < start + length)
	{
		return MyString(m_stringPtr.get(), m_length - start);
	}

	if (m_length - 1 < start)
	{
		return MyString();
	}

	return MyString(m_stringPtr.get(), length);
}

void MyString::Clear()
{
	m_stringPtr.reset();
	m_length = 0;
	m_stringPtr = std::make_unique<char[]>(1);
}

MyString& MyString::operator=(const MyString& other)
{
	if (std::addressof(other) != this)
	{
		MyString tempCopy(other);
		std::swap(m_length, tempCopy.m_length);
		std::swap(m_stringPtr, tempCopy.m_stringPtr);
	}

	return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	if (&other != this)
	{
		m_stringPtr = std::move(other.m_stringPtr);
		m_length = other.m_length;
		other.m_length = 0;
		other.m_stringPtr.reset();
	}

	return *this;
}

MyString MyString::operator+(const MyString& other)
{
	MyString tempString(this->m_stringPtr.get(), this->m_length + other.m_length);

	return tempString += other;
}

MyString& MyString::operator+=(const MyString& other)
{
	MyString tempString(this->GetStringData());

	m_length = tempString.GetLength() + other.GetLength();
	m_stringPtr = std::make_unique<char[]>(tempString.GetLength() + other.GetLength() + 1);

	memmove(m_stringPtr.get(), tempString.GetStringData(), tempString.GetLength());
	memmove(m_stringPtr.get() + tempString.GetLength(), other.GetStringData(), other.GetLength());

	return *this;
}

bool MyString::operator==(const MyString& other) const
{
	if (this->GetLength() != other.GetLength())
	{
		return false;
	}

	for (size_t i = 0; i < other.GetLength(); ++i)
	{
		if (this->m_stringPtr[i] != other.m_stringPtr[i])
		{
			return false;
		}
	}

	return true;
}

bool MyString::operator!=(const MyString& other) const
{
	return !(*this == other);
}

bool MyString::operator<(const MyString& other) const
{
	if (this->GetLength() > other.GetLength())
	{
		return false;
	}

	size_t minLength = other.GetLength();
	for (size_t i = 0; i < minLength; ++i)
	{
		if (this->m_stringPtr[i] > other.m_stringPtr[i])
		{
			return false;
		}
	}
	
	return true;
}

bool MyString::operator>(const MyString& other) const
{
	if (this->GetLength() < other.GetLength())
	{
		return false;
	}

	size_t minLength = other.GetLength();
	for (size_t i = 0; i < minLength; ++i)
	{
		if (this->m_stringPtr[i] < other.m_stringPtr[i])
		{
			return false;
		}
	}

	return true;
}

bool MyString::operator<=(const MyString& other) const
{
	return !(*this > other);
}

bool MyString::operator>=(const MyString& other) const
{
	return !(*this < other);
}

const char& MyString::operator[](size_t index) const
{
	//assert(index < m_length);
	return m_stringPtr[index];
}

char& MyString::operator[](size_t index)
{
	// TODO: check range
	return m_stringPtr[index];
}

std::istream& operator>>(std::istream& inputStream, MyString& myString)
{
	char ch;
	
	do
	{
		inputStream >> ch;
		if (inputStream.good())
		{
			MyString tempString(&ch, 1);
			myString += tempString;
		}
	}
	while (ch != ' ' || inputStream.eof());

	return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, MyString& myString)
{
	size_t length = myString.GetLength();
	for (size_t i = 0; i < length; ++i)
	{
		outputStream << myString[i];
	}

	return outputStream;
}

MyString operator+(const std::string& stlString, const MyString& myString)
{
	MyString tempString(stlString);

	return tempString += myString;
}

MyString operator+(const char* cString, const MyString& myString)
{
	MyString tempString(cString, strlen(cString) + myString.GetLength());

	return tempString += myString;
}
