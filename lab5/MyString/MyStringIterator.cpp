#include "pch.h"
#include "MyStringIterator.h"

//// MyString.h
//typedef MyStringIterator<char> iterator;
//typedef MyStringIterator<const char> const_iterator;
//
//iterator begin();
//iterator end();
//
//const_iterator begin() const;
//const_iterator end() const;
//
//// MyString.cpp
//MyString::iterator MyString::begin()
//{
//	return iterator(m_stringPtr.get());
//}
//
//MyString::iterator MyString::end()
//{
//	return iterator(m_stringPtr.get() + m_length);
//}
//
//MyString::const_iterator MyString::begin() const
//{
//	return const_iterator(m_stringPtr.get());
//}
//
//MyString::const_iterator MyString::end() const
//{
//	return const_iterator(m_stringPtr.get() + m_length);
//}