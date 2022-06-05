#include "pch.h"
#include "MyString.h"
#include "MyStringIterator.hpp"

MyString::MyString()
	: m_stringPtr(std::make_unique<char[]>(1))
	, m_length(0)
{
	// TODO: проиницициалзировать нуль символом здесь и в остальных местах
	m_stringPtr[m_length] = '\0';
}

MyString::MyString(const char* pString)
	: MyString(pString, strlen(pString))
{
	// TODO: memmove(); или
	// TODO: использовать делегирование конструкторов
}

MyString::MyString(const char* pString, size_t length)
	: m_length(length)
	, m_stringPtr(std::make_unique<char[]>(length + 1))
{
	memcpy(m_stringPtr.get(), pString, length);
	m_stringPtr[m_length] = '\0';
}

MyString::MyString(MyString const& other)
	: MyString(other.GetStringData(), other.GetLength())
{
}

MyString::MyString(MyString&& other) noexcept
	: m_length(0)
	, m_stringPtr(nullptr)
{
	// TODO: проверить ситуацию с move того же экземлпяра
	//m_stringPtr = std::move(other.m_stringPtr);
	std::swap(m_length, other.m_length);
	std::swap(m_stringPtr, other.m_stringPtr);
}

MyString::MyString(std::string const& stlString)
	: MyString(stlString.c_str(), stlString.size())
{
	// TODO: либо делегировать конструктор либо memmove c_str()
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
	if (m_length <= start)
	{
		return MyString();
	}

	if (m_length < start + length)
	{
		// TODO: + start
		return MyString(m_stringPtr.get() + start, m_length - start);
	}

	if (m_length - 1 < start)
	{
		return MyString();
	}
	// TODO: + start
	return MyString(m_stringPtr.get() + start, length);
}

void MyString::Clear()
{
	m_length = 0;
	m_stringPtr = std::make_unique<char[]>(m_length + 1);
	// TODO: добавить символ конца строки
	m_stringPtr[m_length] = '\0';
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
	// TODO: добавить addressof()
	// TODO: сделать swap()
	if (std::addressof(other) != this)
	{
		m_length = 0;
		m_stringPtr = nullptr;

		std::swap(m_length, other.m_length);
		std::swap(m_stringPtr, other.m_stringPtr);
	}

	return *this;
}

MyString MyString::operator+(const MyString& other)
{
	// TODO: исправить копирование данных за пределами строки
	MyString tempString(GetStringData());

	return tempString += other;
}

MyString MyString::operator+(const std::string& stlString)
{
	MyString tempString(stlString);

	return *this + tempString;
}

MyString MyString::operator+(const char* cString)
{
	MyString tempString(cString);

	return *this + tempString;
}

MyString& MyString::operator+=(const MyString& other)
{
	// TODO: добавить поддержку нулевых символов
	// TODO: добавить try/catch
	try
	{
		auto tempStringPtr = std::make_unique<char[]>(GetLength() + other.GetLength() + 1);

		memcpy(tempStringPtr.get(), GetStringData(), GetLength());
		memcpy(tempStringPtr.get() + GetLength(), other.GetStringData(), other.GetLength());
		
		m_length = GetLength() + other.GetLength();
		m_stringPtr = std::move(tempStringPtr);
	}
	catch (...)
	{
		return *this;
	}

	m_stringPtr[m_length] = '\0';

	return *this;
}

bool MyString::operator==(const MyString& other) const
{
	if (GetLength() != other.GetLength())
	{
		return false;
	}

	// TODO: использовать strcmp или memcmp версия 
	int cmpResult = memcmp(GetStringData(), other.GetStringData(), other.GetLength());

	return cmpResult == 0;
}

bool MyString::operator!=(const MyString& other) const
{
	return !(*this == other);
}

bool MyString::operator<(const MyString& other) const
{
	// TODO: использовать strcmp или memcmp здесь и дальше
	size_t minLength = GetLength() < other.GetLength() ? GetLength() : other.GetLength();
	int cmpResult = memcmp(GetStringData(), other.GetStringData(), minLength);

	if (GetLength() >= other.GetLength() && cmpResult == 0)
	{
		return false;
	}
	
	return cmpResult <= 0;
}

bool MyString::operator>(const MyString& other) const
{
	return other < *this;
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
	if (index >= m_length)
	{
		throw std::out_of_range("Index out of range");
	}

	return m_stringPtr[index];
}

char& MyString::operator[](size_t index)
{
	if (index >= m_length)
	{
		throw std::out_of_range("Index out of range");
	}

	return m_stringPtr[index];
}

std::istream& operator>>(std::istream& inputStream, MyString& myString)
{
	if (inputStream.fail())
	{
		return inputStream;
	}

	size_t length = 0;
	inputStream >> std::noskipws;
	
	char ch;
	do
	{
		inputStream >> ch;
		if (inputStream.good() && !std::isspace(ch))
		{
			++length;
		}
	}
	while (ch != ' ' && !inputStream.eof());

	if (length == 0)
	{
		return inputStream;
	}

	inputStream.clear();
	inputStream.seekg(0);

	try
	{
		auto buffer = std::make_unique<char[]>(length + 1);
		inputStream.read(buffer.get(), length);
		buffer[length] = '\0';
		myString += MyString(buffer.get(), length);
	}
	catch (const std::bad_alloc& e)
	{
		std::cout << e.what() << std::endl;
	}

	return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, MyString& myString)
{
	// TODO: использовать outputStream.write()
	outputStream.write(myString.GetStringData(), myString.GetLength());

	return outputStream;
}

MyString operator+(const std::string& stlString, const MyString& myString)
{
	MyString tempString(stlString);

	return tempString + myString;
}

MyString operator+(const char* cString, const MyString& myString)
{
	MyString tempString(cString, strlen(cString) + myString.GetLength());

	return tempString + myString;
}

using iterator = MyStringIterator<char>;
using const_iterator = MyStringIterator<const char>;

using const_reverse_iterator = std::reverse_iterator<const_iterator>;
using reverse_iterator = std::reverse_iterator<iterator>;

iterator MyString::begin()
{
	return iterator(m_stringPtr.get());
}

iterator MyString::end()
{
	return iterator(m_stringPtr.get() + m_length);
}

const_iterator MyString::begin() const
{
	return const_iterator(m_stringPtr.get());
}

const_iterator MyString::end() const
{
	return const_iterator(m_stringPtr.get() + m_length);
}

reverse_iterator MyString::rbegin()
{
	return std::make_reverse_iterator(end());
}

reverse_iterator MyString::rend()
{
	return std::make_reverse_iterator(begin());
}

const_reverse_iterator MyString::rbegin() const
{
	return std::make_reverse_iterator(end());
}

const_reverse_iterator MyString::rend() const
{
	return std::make_reverse_iterator(begin());
}


