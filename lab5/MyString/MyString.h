#pragma once
#include "pch.h"

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
	MyString(MyString&& other);

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

private:
	size_t m_length;
	std::unique_ptr<char[]> m_stringPtr;
};
