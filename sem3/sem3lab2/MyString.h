class MyString
{
private:
	char* m_pStr;		// Элемент данных класса (адрес строки)
public:
    MyString ();
	MyString (char* s);	// Объявление конструктора
    MyString(const MyString& str);
    ~MyString();		// Объявление деструктора

    MyString& operator=(const MyString &str);


	void Copy (char* s);
	char* GetString() const;	// Объявление метода (accessor)
	size_t GetLength();	// Объявление метода (длина строки)
};
