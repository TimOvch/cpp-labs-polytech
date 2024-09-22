
#ifndef _BOOK_H_
#define _BOOK_H_
#include "InAndOut.hpp"
#include <wchar.h>

#define DEFSTRSIZE 10
extern const char* categoriesMas[];

enum categories{
    fantasy,
    fantastic,
    detective,
    novel,
    buisness,
    scientific,
    compScie,
    psycology,
    history,
    forkids,
    numOfCats
};

struct BOOK{
    char* author;
    char* title;
    int year;
    double price;
    categories category;
    
    BOOK(){
        author = nullptr;
        title = nullptr;
        year = 0;
        price = 0;
        category = numOfCats;
    }
    
    ~BOOK(){
        delete[] author;
        delete[] title;
    }
};

#endif
