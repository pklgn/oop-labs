#pragma once
#include "pch.h"
#include "MyStringIterator.hpp"

class MyString
{
public:
	// ����������� �� ���������
	MyString();

	// �����������, ���������������� ������ ������� ������
	// � ����������� ������� ��������
	MyString(const char* pString);

	// �����������, ���������������� ������ ������� ��
	// ����������� ������� �������� �����
	MyString(const char* pString, size_t length);

	// ����������� �����������
	MyString(MyString const& other);

	// ������������ ����������� (��� ������������, ����������� � C++11)
	//  ����������� ��������� � ������������ ���������� ������������
	MyString(MyString&& other) noexcept;

	// �����������, ���������������� ������ ������� ��
	// ������ ����������� ���������� C++
	MyString(std::string const& stlString);

	// ���������� ����� ������ (��� ����� ������������ �������� �������)
	size_t GetLength() const;

	// ���������� ��������� �� ������ �������� ������.
	// � ����� ������� ����������� ������ ���� ����������� ������� ������
	// ���� ���� ������ ������
	const char* GetStringData() const;

	// ���������� ��������� � �������� ������� ������ �� ������ length ��������
	MyString SubString(size_t start, size_t length = SIZE_MAX) const;

	// ������� ������ (������ ���������� ����� ������� �����)
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
