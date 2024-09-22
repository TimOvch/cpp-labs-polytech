#ifndef _INANDOUT_H_
#define _INANDOUT_H_
#include <fstream>
#include <wchar.h>
struct BOOK;
struct bookLib;
extern FILE* file;
// Константы:
#define DEFAULT_BUFFER_SIZE 50
#define BUFFER_DELTA 50
#define MAX_STRING_LEN 3000
#define PISMENNOST_EXIST -3000
#define YEAR_NOW 2023
#define MIN_MONETARY_UNIT_NUM 2
#define MAX_BOOK_PRICE 2785829200 //Cамая дорогая книга на планете в рублях
#define STRING_BREAK_FLAG "*"
#define CHAR_BREAK_FLAG '*'
#define YEAR_BREAK_FLAG -3001
#define PRICE_BREAK_FLAG -1
#define CATEGORY_BREAK_FLAG numOfCats
#define LIBRARY_INDEX_BREAK_FLAG -1
#define FILE_BREAK_SYMBOL '|'
#define FILE_DIVIDE_SYMBOL |
//Объявления функций
void getStr(char*& str,const char* enterInfo);
void authorIsSave();
void titleIsSave();
void maxLenStrError(char*& str,const char* enterInfo);
int getYear();
void yearIsSave();
double getPrice();
void priceIsSave();
int getCategory();
void categoryIsSave();
void printCategories();
void printBook(BOOK* book);
void printLib(BOOK** books, int booksNum);
int getLibIndex(int booksNum, const char *enterInfo);
void messageDelBook();
void messageDelBooks();
void putBooksInFile(bookLib* library);;
void getBooksFromFile(bookLib* library);
void printMenu(int booksNum);
void printSortMenu();
#endif
