//
//  Reader.hpp
//  Lisp
//
//  Created by Тимофей Овчинников on 03.03.2024.
//

#ifndef Reader_hpp
#define Reader_hpp

#include <stdio.h>

#define defaultBufSz 200
#define bufSzDelta 100
#define stopSymbol ';'

class MyString;
void READ(MyString& string);

#endif
