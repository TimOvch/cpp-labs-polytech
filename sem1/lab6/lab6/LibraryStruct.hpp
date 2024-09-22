#ifndef _LIBRARYSTRUCT_H_
#define _LIBRARYSTRUCT_H_
#define DEFAULT_LIBRARY_SIZE 5
#include "InAndOut.hpp"
#include "Helping.h"
#include "Book.hpp"
struct bookLib;
//структура библиотеки
struct bookLib{
    int booksNum;
    BOOK** books;
    double avYear;
    
    bookLib(){
        booksNum = 0;
        books = new BOOK*[booksNum];
        avYear = 0;
    }
    
    ~bookLib(){
        for(int i = 0; i < booksNum; i++){
            delete books[i];
        }
        delete[] books;
    }
    
    void addNewBook(){
        int prevSize = booksNum;
        int newsize = prevSize+1;
        BOOK** newBooks = new BOOK*[newsize];
        
        for(int i = 0; i < prevSize; i++){
            newBooks[i] = books[i];
        }
        
        delete[] books;
        books = newBooks;
        books[booksNum] = new BOOK;
        booksNum++;
        getStr(books[booksNum-1]->title,"Введите название книги:");
        if(MyStrCmp(books[booksNum-1]->title, "*") == 0){
            delete books[booksNum-1];
            booksNum--;
            return;
        } else{
            titleIsSave();
        }
        getStr(books[booksNum-1]->author,"Введите имя автора:");
        if(MyStrCmp(books[booksNum-1]->author, "*") == 0){
            delete books[booksNum-1];
            booksNum--;
            return;
        }else{
            authorIsSave();
        }
        books[booksNum-1]->year = getYear();
        if(books[booksNum-1]->year == YEAR_BREAK_FLAG){
            delete books[booksNum-1];
            booksNum--;
            return;
        } else{
            yearIsSave();
        }
        books[booksNum-1]->price = getPrice();
        if(books[booksNum-1]->price == PRICE_BREAK_FLAG){
            delete books[booksNum-1];
            booksNum--;
            return;
        } else{
            priceIsSave();
        }
        books[booksNum-1]->category = categories(getCategory());
        if(books[booksNum-1]->category == numOfCats){
            delete books[booksNum-1];
            booksNum--;
            return;
        } else{
            categoryIsSave();
        }
        
        printf("\nКнига успешно добавлена!\n");
    }
    
    void printBooksLib(){
        printLib(books, booksNum);
    }
    
    void deleteBook(){
        printBooksLib();
        int index = getLibIndex(booksNum, "\nЧтобы вернуться в главное меню введите *\nВведите номер книги, которую нужно удалить:");
        if(index == -1){
            return;
        }
        printf("\n----------\nКнига №%d", index+1);
        printBook(books[index]);
        printf("\n");
        
        int sure = getLibIndex(2, "\nВы уверенны, что хотите удалить книгу?\n1 - уверен(а)\n2 - вернуться в меню\nВведите значение:");
        
        if(sure == 0){
            delete books[index];
            for(int i = index+1; i < booksNum; i++){
                books[i-1] = books[i];
            }
            booksNum--;
            messageDelBook();
        } else if(sure == 1 || sure == -1){
            return;
        }
    }
    
    void deleteDiapBooks(){
        printBooksLib();
        int indexFirst = getLibIndex(booksNum, "\nЧтобы вернуться в главное меню введите *\nВведите номер книги, с которой нужно удалить(включительно):");
        if(indexFirst == -1){
            return;
        }
        int indexLast = getLibIndex(booksNum, "\nЧтобы вернуться в главное меню введите *\nВведите номер книги, по которую нужно удалить(включительно):");
        if(indexLast == -1){
            return;
        }
        
        while(indexFirst > indexLast){
            printf("\nЗначение начального номера больше конечного, попробуйте снова!\n");
            indexFirst = getLibIndex(booksNum, "\nЧтобы вернуться в главное меню введите *\nВведите номер книги, с которой нужно удалить(включительно):");
            if(indexFirst == -1){
                return;
            }
            indexLast = getLibIndex(booksNum, "\nЧтобы вернуться в главное меню введите *\nВведите номер книги, по которую нужно удалить(включительно):");
            if(indexLast == -1){
                return;
            }
        }
        
        for(int i = indexFirst; i <= indexLast; i++){
            printf("\n----------\nКнига №%d", i+1);
            printBook(books[i]);
        }
        printf("\n");
        
        int sure = getLibIndex(2, "\nВы уверенны, что хотите удалить книги?\n1 - уверен(а)\n2 - вернуться в меню\nВведите значение:");
        
        if(sure == 0){
            for(int i = indexFirst; i <= indexLast; i++){
                delete books[i];
            }
            
            for(int i = indexLast+1; i < booksNum; i++){
                books[i-(indexLast-indexFirst+1)] = books[i];
            }
            
            booksNum-=(indexLast-indexFirst+1);
            
            messageDelBooks();
        }
    }
    
    void countAvYear(){
        double sumYear = 0;
        for(int i = 0; i < booksNum; i++){
            sumYear+=books[i]->year;
        }
        avYear = sumYear/booksNum;
    }
    
};

#endif
