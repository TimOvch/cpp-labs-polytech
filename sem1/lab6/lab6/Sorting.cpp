// ФАЙЛ СОРТИРОВОК
#include "LibraryStruct.hpp"
#include "Book.hpp"

void sortAuthor(bookLib* library){
    for(int i = 0; i < library->booksNum-1; i++){
        int indMin = i;
        for(int j = i+1; j < library->booksNum; j++){
            if(MyStrCmp((library->books)[j]->author, (library->books)[indMin]->author) == -1){
                indMin = j;
            }
        }
        BOOK* tmp =(library->books)[i];
        (library->books)[i] = (library->books)[indMin];
        (library->books)[indMin] = tmp;
    }
}

void sortTitle(bookLib* library){
    for(int i = 0; i < library->booksNum-1; i++){
        int indMin = i;
        for(int j = i+1; j < library->booksNum; j++){
            if(MyStrCmp((library->books)[j]->title, (library->books)[indMin]->title) == -1){
                indMin = j;
            }
        }
        BOOK* tmp =(library->books)[i];
        (library->books)[i] = (library->books)[indMin];
        (library->books)[indMin] = tmp;
    }
}

void sortYear(bookLib* library){
    for(int i = 0; i < library->booksNum-1; i++){
        int indMin = i;
        for(int j = i+1; j < library->booksNum; j++){
            if((library->books)[j]->year < (library->books)[indMin]->year){
                indMin = j;
            }
        }
        BOOK* tmp =(library->books)[i];
        (library->books)[i] = (library->books)[indMin];
        (library->books)[indMin] = tmp;
    }
}

void sortPrice(bookLib* library){
    for(int i = 0; i < library->booksNum-1; i++){
        int indMin = i;
        for(int j = i+1; j < library->booksNum; j++){
            if((library->books)[j]->price < (library->books)[indMin]->price){
                indMin = j;
            }
        }
        BOOK* tmp =(library->books)[i];
        (library->books)[i] = (library->books)[indMin];
        (library->books)[indMin] = tmp;
    }
}

void sortCategory(bookLib* library){
    for(int i = 0; i < library->booksNum-1; i++){
        int indMin = i;
        for(int j = i+1; j < library->booksNum; j++){
            if((library->books)[j]->category < (library->books)[indMin]->category){
                indMin = j;
            }
        }
        BOOK* tmp =(library->books)[i];
        (library->books)[i] = (library->books)[indMin];
        (library->books)[indMin] = tmp;
    }
}

