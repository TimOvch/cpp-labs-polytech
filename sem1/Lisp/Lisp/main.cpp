//
//  main.cpp
//  Lisp
//
//  Created by Тимофей Овчинников on 03.03.2024.
//

#include <stdio.h>
#include "LispValue.hpp"
#include "Code.hpp"

int main(){
    
    MyString code;
    
    READ(code);
    
    std::cout << code;
    
    return 0;
}
