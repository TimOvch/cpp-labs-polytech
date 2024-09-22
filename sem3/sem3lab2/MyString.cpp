#include "stdafx.h"
#include "MyString.h"

void MyString::Copy (char* s)
{
	delete [] m_pStr;
	// Динамически выделяем требуемое количество памяти.
	int len = strlen(s) + 1;
	m_pStr = new char[len];
	// + 1, так как нулевой байт тоже нужно скопировать
	// Если память выделена, копируем строку-аргумент в строку-член класса
	if (m_pStr)
		std::strcpy(m_pStr, s);
}

// Определение конструктора.
MyString::MyString (char* s)
{
	m_pStr = nullptr;
	Copy(s);
}

// Определение деструктора.
MyString::~MyString()
{
	// Освобождение памяти, занятой в конструкторе для строки-члена класса
	delete[] m_pStr;
}

// Метод класса
char* MyString::GetString() const
{
	return m_pStr;
}

size_t MyString::GetLength()
{
	return strlen(m_pStr) + 1;
}

MyString::MyString() {
    m_pStr = nullptr;
}

MyString &MyString::operator=(const MyString &str) {
    if(&str == this){
        return *this;
    }
    Copy(str.GetString());
    return *this;
}

MyString::MyString(const MyString &str) {
    m_pStr = nullptr;
    Copy(str.GetString());
}

