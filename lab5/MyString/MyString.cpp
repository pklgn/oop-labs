#include "pch.h"
#include "MyString.h"

MyString::MyString()
	: m_stringPtr(std::make_unique<char[]>(1))
	, m_length(0)
{
	// TODO: проиницициалзировать нуль символом здесь и в остальных местах
	m_stringPtr[m_length] = '\0';
}

MyString::MyString(const char* pString)
	: MyString(pString, std::strlen(pString))
{
	// TODO: memmove(); или
	// TODO: использовать делегирование конструкторов
}

MyString::MyString(const char* pString, size_t length)
	: m_length(length)
	, m_stringPtr(std::make_unique<char[]>(length + 1))
{
	std::memmove(m_stringPtr.get(), pString, length);
	m_stringPtr[m_length] = '\0';
}

MyString::MyString(MyString const& other)
	: MyString(other.GetStringData(), other.GetLength())
{
}

MyString::MyString(MyString&& other) noexcept
	: m_length(0)
{
	// TODO: проверить ситуацию с move того же экземлпяра
	m_stringPtr = std::move(other.m_stringPtr);
	std::swap(m_length, other.m_length);
}

MyString::MyString(std::string const& stlString)
	: MyString(stlString.c_str(), stlString.length())
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
	// TODO: добавить символ конца строки или делегировать MyString()
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
	// TODO: копирование данных за пределами строки
	MyString tempString(this->GetStringData());

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

	// TODO: узнать можно ли делегировать

	return *this + tempString;
}

MyString& MyString::operator+=(const MyString& other)
{
	// TODO: добавить поддержку нулевых символов
	MyString tempString(this->GetStringData());

	// TODO: добавить try/catch
	try
	{
		m_length = tempString.GetLength() + other.GetLength();
		m_stringPtr = std::make_unique<char[]>(tempString.GetLength() + other.GetLength() + 1);
		memmove(m_stringPtr.get(), tempString.GetStringData(), tempString.GetLength());
		memmove(m_stringPtr.get() + tempString.GetLength(), other.GetStringData(), other.GetLength());
	}
	catch (...)
	{
		m_stringPtr = std::make_unique<char[]>(tempString.GetLength() + 1);

		throw;
	}

	m_stringPtr[m_length] = '\0';

	return *this;
}

bool MyString::operator==(const MyString& other) const
{
	if (this->GetLength() != other.GetLength())
	{
		return false;
	}
	// TODO: использовать strcmp или memcmp версия 
	int cmpResult = std::memcmp(this->GetStringData(), other.GetStringData(), other.GetLength());

	return cmpResult == 0;
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
	// TODO: использовать strcmp или memcmp здесь и дальше
	size_t minLength = this->GetLength();
	int cmpResult = std::memcmp(this->GetStringData(), other.GetStringData(), minLength);

	if (this->GetLength() == other.GetLength())
	{
		if (cmpResult == 0)
		{
			return false;
		}
	}
	
	return cmpResult <= 0;
}

bool MyString::operator>(const MyString& other) const
{
	if (this->GetLength() < other.GetLength())
	{
		return false;
	}

	size_t minLength = other.GetLength();
	int cmpResult = std::memcmp(this->GetStringData(), other.GetStringData(), minLength);

	if (this->GetLength() == other.GetLength())
	{
		if (cmpResult == 0)
		{
			return false;
		}
	}
	// TODO: делегировать операторам != и <

	return cmpResult >= 0;
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
	char ch;
	if (inputStream.fail())
	{
		return inputStream;
	}

	size_t length = 0;
	inputStream >> std::noskipws;
	do
	{
		inputStream >> ch;
		if (inputStream.good() && !std::isspace(ch))
		{
			++length;
		}
	}
	while (ch != ' ' && !inputStream.eof());

	if (length > 0)
	{
		inputStream.clear();
		inputStream.seekg(0);
		char* buffer = new char[length];
		inputStream.read(buffer, length);
		myString += MyString(buffer, length);
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
