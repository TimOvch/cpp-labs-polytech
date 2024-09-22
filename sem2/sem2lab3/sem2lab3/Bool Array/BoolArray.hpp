//
//  BoolArray.hpp
//  sem2lab3
//
//  Created by Тимофей Овчинников on 22.02.2024.
//

#ifndef BoolArray_hpp
#define BoolArray_hpp

#include <iostream>

struct Byte{
    bool bit1:1;
    bool bit2:1;
    bool bit3:1;
    bool bit4:1;
    bool bit5:1;
    bool bit6:1;
    bool bit7:1;
    bool bit8:1;
};

union ByteSet{
    Byte byte;
    unsigned char setter;
};

class Trade{
private:
    size_t bytenum;
    size_t bitnum;
    bool flag;
    ByteSet* masptr;
    
public:
    Trade();
    Trade(size_t bytenum, size_t bitnum, bool flag, ByteSet* masptr);
    Trade& operator=(Trade& trader);
    Trade& operator=(bool flag);
    // TODO: почитайте, какие еще операторы можно перегрузить
    // hint: все ниже реализуется одной перегрузкой
    operator bool() const;
//    bool operator!();
//    friend bool operator||(Trade trader1, Trade trader2);
//    friend bool operator||(bool flag, Trade trader);
//    friend bool operator||(Trade trader, bool flag);
//    friend bool operator==(Trade trader1, Trade trader2);
//    friend bool operator==(bool flag, Trade trader);
//    friend bool operator==(Trade trader, bool flag);
//    friend bool operator!=(Trade trader1, Trade trader2);
//    friend bool operator!=(bool flag, Trade& trader);
//    friend bool operator!=(Trade trader, bool flag);
//    friend bool operator&&(Trade trader1, Trade trader2);
//    friend bool operator&&(bool flag, Trade trader);
//    friend bool operator&&(Trade trader, bool flag);
    friend std::ostream& operator<<(std::ostream& stream, Trade trader);
};

class BoolArray{
private:
    ByteSet* bytemas;
    size_t sizeBit;
    size_t sizeByte;
    
public:
    //конструкторы
    BoolArray();
    BoolArray(const size_t Size, bool flag = false);
    BoolArray(BoolArray& arr);
    //деструктор
    ~BoolArray();
    //операторы
    BoolArray& operator=(BoolArray& from);
    Trade operator[](size_t index);
    //сеттер
    void SetArray(size_t Size, bool Flag);
    //Геттер размера
    size_t size();
    void resize(size_t Size, bool Flag = false);
};
#endif /* BoolArray_hpp */
