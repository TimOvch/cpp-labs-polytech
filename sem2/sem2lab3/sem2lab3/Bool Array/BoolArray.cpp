#include "BoolArray.hpp"

Trade::Trade(){
    bytenum = 0;
    bitnum = 0;
    flag = 0;
    masptr = nullptr;
}
Trade::Trade(size_t bytenum, size_t bitnum, bool flag, ByteSet* masptr)
: bytenum(bytenum), bitnum(bitnum), flag(flag), masptr(masptr)
{}

Trade& Trade::operator=(bool Flag){
    if(masptr!=nullptr){
        switch (bitnum) {
            case 0:
                masptr[bytenum].byte.bit1 = Flag;
                break;
            case 1:
                masptr[bytenum].byte.bit2 = Flag;
                break;
            case 2:
                masptr[bytenum].byte.bit3 = Flag;
                break;
            case 3:
                masptr[bytenum].byte.bit4 = Flag;
                break;
            case 4:
                masptr[bytenum].byte.bit5 = Flag;
                break;
            case 5:
                masptr[bytenum].byte.bit6 = Flag;
                break;
            case 6:
                masptr[bytenum].byte.bit7 = Flag;
                break;
            case 7:
                masptr[bytenum].byte.bit8 = flag;
                break;
        }
        flag = Flag;
    }
    return *this;
}

Trade& Trade::operator=(Trade& trader){
    if(trader.masptr != nullptr){
        *this = trader.flag;
    }
    return *this;
}

//логические операторы
Trade::operator bool() const{
    return flag;
}

//bool Trade::operator!(){
//    return !flag;
//}
//bool operator||(Trade trader1, Trade trader2){
//    return trader1.flag || trader2.flag;
//}
//bool operator||(bool flag, Trade trader){
//    return flag||trader.flag;
//}
//bool operator||(Trade trader, bool flag){
//    return flag||trader;
//}
//bool operator==(Trade trader1, Trade trader2){
//    return trader1.flag == trader2.flag;
//}
//bool operator==(bool flag, Trade trader){
//    return flag == trader.flag;
//}
//bool operator==(Trade trader, bool flag){
//    return flag == trader;
//}
//bool operator!=(Trade trader1, Trade trader2){
//    return !(trader1==trader2);
//}
//bool operator!=(bool flag, Trade& trader){
//    return !(flag == trader);
//}
//bool operator!=(Trade trader, bool flag){
//    return flag != trader;
//}
//bool operator&&(Trade trader1, Trade trader2){
//    return trader1.flag && trader2.flag;
//}
//bool operator&&(bool flag, Trade trader){
//    return trader.flag && flag;
//}
//bool operator&&(Trade trader, bool flag){
//    return flag&&trader;
//}

//Оператор <<
std::ostream& operator<<(std::ostream& stream, Trade trader){
    stream << trader.flag;
    return stream;
}

//конструкторы
BoolArray::BoolArray(){
    sizeBit = 0;
    sizeByte = 0;
    bytemas = new ByteSet[sizeByte];
}

BoolArray::BoolArray(const size_t Size, bool flag)
: BoolArray()
{
    SetArray(Size, flag);
}

BoolArray::BoolArray(BoolArray& arr)
: BoolArray()
{
    if(arr.bytemas == nullptr) return;
    
    *this = arr;
}

//деструктор
BoolArray::~BoolArray(){
    if(bytemas!=nullptr) delete bytemas;
}

//операторы
BoolArray& BoolArray::operator=(BoolArray& from){
    if(bytemas != nullptr) delete bytemas;
    
    if(from.bytemas == nullptr){
        bytemas = nullptr;
        sizeBit = 0;
        sizeByte = 0;
    }
    
    sizeByte = from.sizeByte;
    sizeBit = from.sizeBit;
    bytemas = new ByteSet[sizeByte];
    
    for(size_t i = 0; i < sizeByte; i++){
        bytemas[i].setter = from.bytemas[i].setter;
    }
    
    return *this;
}

Trade BoolArray::operator[](size_t index){
    if(index<sizeBit){
        size_t bytenum = index/8;
        size_t bitnum = index - bytenum*8;
        
        bool bit = bytemas[bytenum].byte.bit1;
        
        switch (bitnum) {
            case 1:
                bit = bytemas[bytenum].byte.bit2;
                break;
            case 2:
                bit = bytemas[bytenum].byte.bit3;
                break;
            case 3:
                bit = bytemas[bytenum].byte.bit4;
                break;
            case 4:
                bit = bytemas[bytenum].byte.bit5;
                break;
            case 5:
                bit = bytemas[bytenum].byte.bit6;
                break;
            case 6:
                bit = bytemas[bytenum].byte.bit7;
                break;
            case 7:
                bit = bytemas[bytenum].byte.bit8;
                break;
        }
        return Trade{bytenum,bitnum,bit,bytemas};
    } else { 
        return Trade{0,0,0,nullptr};
    }
}

//сеттер
void BoolArray::SetArray(size_t Size, bool Flag){
    if(bytemas!= nullptr) delete bytemas;
    
    sizeBit = Size;
    sizeByte = ceil(Size/8.);
    
    bytemas = new ByteSet[sizeByte];
    
    for(size_t i = 0; i < sizeByte; i++ ){
        if(Flag){
            bytemas[i].setter = 0xFF;
        } else{
            bytemas[i].setter = 0;
        }
    }
}

//геттер размера
size_t BoolArray::size(){
    return sizeBit;
}

void BoolArray::resize(size_t Size, bool Flag){
    size_t nByte = ceil(Size/8.);
    if(sizeBit == Size){
        return;
    } else if(Size < sizeBit){
        if(nByte != sizeByte){
            ByteSet* newbytemas = new ByteSet[nByte];
            for(size_t i = 0; i < nByte; i++){
                newbytemas[i].setter = bytemas[i].setter;
            }
            delete[] bytemas;
            bytemas = newbytemas;
        }
    } else{
        if(nByte != sizeByte){
            ByteSet* newbytemas = new ByteSet[nByte];
            for(size_t i = 0; i < sizeByte; i++){
                newbytemas[i].setter = bytemas[i].setter;
            }
            delete[] bytemas;
            bytemas = newbytemas;
            for(size_t i = sizeByte; i < nByte; i++){
                if(Flag){
                    bytemas[i].setter = 0xFF;
                } else{
                    newbytemas[i].setter = 0;
                }
            }
            for(size_t i = 7; i > 7-(sizeByte*8)+sizeBit; i--){
                if(Flag){
                    bytemas[sizeByte-1].setter|=(1<<i);
                } else{
                    bytemas[sizeByte-1].setter&=~(1<<i);
                }
            }
        } else{
            for(size_t i = 7-(sizeByte*8-Size); i > 7-(sizeByte*8 - sizeBit); i--){
                if(Flag){
                    bytemas[sizeByte-1].setter|=1<<i;
                } else{
                    bytemas[sizeByte-1].setter&=~(1<<i);
                }
            }
        }
    }
    
    sizeBit = Size;
    sizeByte = nByte;
}
