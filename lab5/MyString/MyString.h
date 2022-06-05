#pragma once
#include "pch.h"
#include "MyStringIterator.hpp"

class MyString
{
public:
	// конструктор по умолчанию
	MyString();

	// конструктор, инициализирующий строку данными строки
	// с завершающим нулевым символом
	MyString(const char* pString);

	// конструктор, инициализирующий строку данными из
	// символьного массива заданной длины
	MyString(const char* pString, size_t length);

	// конструктор копирования
	MyString(MyString const& other);

	// перемещающий конструктор (для компиляторов, совместимых с C++11)
	//  реализуется совместно с перемещающим оператором присваивания
	MyString(MyString&& other) noexcept;

	// конструктор, инициализирующий строку данными из
	// строки стандартной библиотеки C++
	MyString(std::string const& stlString);

	// возвращает длину строки (без учета завершающего нулевого символа)
	size_t GetLength() const;

	// возвращает указатель на массив символов строки.
	// В конце массива обязательно должен быть завершающий нулевой символ
	// даже если строка пустая
	const char* GetStringData() const;

	// возвращает подстроку с заданной позиции длиной не больше length символов
	MyString SubString(size_t start, size_t length = SIZE_MAX) const;

	// очистка строки (строка становится снова нулевой длины)
	void Clear();

	MyString& operator=(const MyString& other);
	MyString& operator=(MyString&& other) noexcept;
	MyString operator+(const MyString& other);
	MyString operator+(const std::string& stlString);
	MyString operator+(const char* cString);
	MyString& operator+=(const MyString& other);
	bool operator==(const MyString& other) const;
	bool operator!=(const MyString& other) const;
	bool operator<(const MyString& other) const;
	bool operator>(const MyString& other) const;
	bool operator<=(const MyString& other) const;
	bool operator>=(const MyString& other) const;
	const char& operator[](size_t index) const;
	char& operator[](size_t index);
	friend std::istream& operator>>(std::istream& inputStream, MyString& myString);
	friend std::ostream& operator<<(std::ostream& outputStream, MyString& myString);

	using iterator = MyStringIterator<char>;
    using const_iterator = MyStringIterator<const char>;

	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	using reverse_iterator = std::reverse_iterator<iterator>;

	iterator begin();
	iterator end();

	const_iterator begin() const;
	const_iterator end() const;

	reverse_iterator rbegin();
	reverse_iterator rend();

	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;

private:
	size_t m_length;
	std::unique_ptr<char[]> m_stringPtr;
};

MyString operator+(const std::string& stlString, const MyString& myString);
MyString operator+(const char* cString, const MyString& myString);
