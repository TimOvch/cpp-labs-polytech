// ФАЙЛ ВВОДА/ВЫВОДА
#include <cstdio>
#include "Helping.h"
#include "InAndOut.hpp"
#include "Book.hpp"
#include "LibraryStruct.hpp"
#include <unistd.h>

FILE* file;
//Функции ввода
void getStr(char*& str,const char* enterInfo){
    int bufForNow = DEFAULT_BUFFER_SIZE, i = 0;
    char* tempDynStr = new char[bufForNow];
    tempDynStr[0] = '\0';
    printf("\nЧтобы вернуться в главное меню введите *\nПри вводе учтите:\nМаксимальное количество символов: %d\n", MAX_STRING_LEN);
    printf("%s", enterInfo);
    fflush(stdin);
    
    char symbol = '\0';
    
    while(true){
        scanf("%c",&symbol);
        
        if(symbol == '\n'){
            break;
        } else if(symbol == FILE_BREAK_SYMBOL){
            continue;
        }
        
        if(symbol>= ' ' && symbol <= '~'){
            tempDynStr[i] = symbol;
            i++;
            if(i > bufForNow-1){
                bufForNow+=BUFFER_DELTA;
                if(bufForNow >= MAX_STRING_LEN){
                    delete []tempDynStr;
                    maxLenStrError(str, enterInfo);
                }
                char* newDynStr = new char[bufForNow];
                strCopy(tempDynStr, newDynStr);
                delete[] tempDynStr;
                tempDynStr = newDynStr;
            }
        }
    }
    str = tempDynStr;
}

void authorIsSave(){
    printf("Автор сохранён!\n");
}

void titleIsSave(){
    printf("Название сохранено!\n");
}

void maxLenStrError(char*& str,const char* enterInfo){
    printf("\nВаша строка превысила максимально возможную длину! Попробуйте снова:");
    getStr(str,enterInfo);
}

int getYear(){
    int res = 0;
    int index = 0;
    bool ifNegative = 0;
    bool breakFlag = 0;
    printf("\nЧтобы вернуться в главное меню введите *\nПри вводе учтите:\n1)Год до нашей эры вводить с минусом(-)\n2)Значение не может быть меньше %d (%d до Н.Э.)\n3)Значение не может быть больше %d\nВведите год:", PISMENNOST_EXIST, -PISMENNOST_EXIST, YEAR_NOW);
    fflush(stdin);
    char symbol = '\0';
    
    while(true){
        scanf("%c", &symbol);
        
        if(symbol == '\n'){
            if(index!=0 || breakFlag == 1){
                break;
            } else {
                printf("\nВы ничего не ввели!\nПробуйте снова:");
                res = getYear();
                return res;
            }
        }
        
        if(symbol>= ' ' && symbol <= '~'){
            if(symbol >= '0' && symbol <= '9'){
                if(breakFlag){
                    printf("\nВы ввели символ %c отличный от цифр!\nПробуйте снова:",CHAR_BREAK_FLAG);
                    res = getYear();
                    return res;
                }
                res = res*10+(symbol-'0');
                index++;
            } else if(symbol == '-' && index == 0){
                if(breakFlag==1){
                    printf("\nВы ввели символ %c отличный от цифр!\nПробуйте снова:",CHAR_BREAK_FLAG);
                    res = getPrice();
                    return res;
                }
                ifNegative = 1;
            } else if(symbol == CHAR_BREAK_FLAG && index == 0){
                if(breakFlag){
                    printf("\nВы ввели символ %c отличный от цифр!\nПробуйте снова:",CHAR_BREAK_FLAG);
                    res = getYear();
                    return res;
                }
                breakFlag = 1;
            } else{
                printf("\nВы ввели символ %c отличный от цифр!\nПробуйте снова:",CHAR_BREAK_FLAG);
                res = getYear();
                return res;
            }
        }
    }
        
    if(breakFlag){
        return YEAR_BREAK_FLAG;
    }
    if(ifNegative){
        res = -res;
    }
    if(res >= PISMENNOST_EXIST && res <= YEAR_NOW && index < 5){
        return res;
    } else{
        printf("\nВы ввели год, выходящий за диапазон!\nПопробуйте снова:");
        res = getYear();
        return res;
    }
        
}

int getLibIndex(int booksNum, const char *enterInfo){
    int res = 0;
    int index = 0;
    bool breakFlag = 0;
    printf("%s", enterInfo);
    fflush(stdin);
    char symbol = '\0';
    
    while(true){
        scanf("%c", &symbol);
        
        if(symbol == '\n'){
            break;
        }
        if(symbol>= ' ' && symbol <= '~'){
            if(symbol >= '0' && symbol <= '9'){
                if(breakFlag){
                    printf("\nВы ввели символ %c отличный от цифр!\nПробуйте снова:",CHAR_BREAK_FLAG);
                    res = getLibIndex(booksNum, enterInfo);
                    return res;
                }
                res = res*10+(symbol-'0');
                index++;
            } else if(symbol == '-' && index == 0){
                printf("\nВы ввели отрицательное значение!\nПробуйте снова:");
                res = getLibIndex(booksNum, enterInfo);
                return res;
            } else if(symbol == CHAR_BREAK_FLAG && index == 0){
                if(breakFlag){
                    printf("\nВы ввели символ %lc отличный от цифр!\nПробуйте снова:",CHAR_BREAK_FLAG);
                    res = getLibIndex(booksNum, enterInfo);
                    return res;
                }
                breakFlag = 1;
            } else{
                printf("\nВы ввели символ %c отличный от цифр!\nПробуйте снова:",symbol);
                res = getLibIndex(booksNum, enterInfo);
                return res;
            }
        }
    }
    if(breakFlag){
        return LIBRARY_INDEX_BREAK_FLAG;
    }
    if(res >= 1 && res <= booksNum && index < 10){
        return res-1;
    } else{
        printf("\nВы ввели значение, выходящее за диапазон!\nПопробуйте снова:");
        res = getLibIndex(booksNum, enterInfo);
        return res;
    }
}

void yearIsSave(){
    printf("Год сохранён!\n");
}

double getPrice(){
    double res = 0;
    double mantis = 0;
    bool ifMantis = 0;
    bool breakFlag = 0;
    double afterFactor = 1.0;
    int kolDoDot = 0, kolPosDot = 0;
    printf("\nЧтобы вернуться в главное меню введите *\nПри вводе учтите:\n1)Цена не может быть отрицательной\n2)Цена не может превышать %ld рублей\n3)Цена не может иметь более %d знаков после точки\n3)Для дробной части можно использовать как точку(.), так и запятую(,)\nВведите цену в рублях:",MAX_BOOK_PRICE, MIN_MONETARY_UNIT_NUM);
    fflush(stdin);
    char symbol = '\0';
    
    while(true){
        scanf("%c", &symbol);
        
        if(symbol == '\n'){
            break;
        }
        if(symbol>= ' ' && symbol <= '~'){
            if(symbol >= '0' && symbol <= '9'){
                if(breakFlag==1){
                    printf("\nВы ввели символ %c отличный от цифр!\nПробуйте снова:",CHAR_BREAK_FLAG);
                    res = getPrice();
                    return res;
                }
                if(ifMantis){
                    kolPosDot++;
                    if(kolPosDot > MIN_MONETARY_UNIT_NUM){
                        printf("\nВы ввели больше %d знаков после точки, денежные валюты не имеют таких делений!\nПробуйте снова:", MIN_MONETARY_UNIT_NUM);
                        res = getPrice();
                        return res;
                    }
                    afterFactor*=0.1;
                    mantis = mantis + (symbol-'0')*afterFactor;
                } else{
                    kolDoDot++;
                    res = res*10+(symbol-'0');
                    if(res > MAX_BOOK_PRICE){
                        printf("\nВы ввели значение больше максимального!\nПробуйте снова:");
                        res = getPrice();
                        return res;
                    }
                }
            } else if(symbol == '.' || symbol == ','){
                if(breakFlag==1){
                    printf("\nВы ввели символ %c отличный от цифр!\nПробуйте снова:",CHAR_BREAK_FLAG);
                    res = getPrice();
                    return res;
                }
                if(kolDoDot!=0){
                    ifMantis = 1;
                } else{
                    printf("\nВы не ввели целую часть\nПробуйте снова:");
                    res = getPrice();
                    return res;
                }
            } else if(symbol == '-' && kolDoDot == 0 && kolPosDot == 0){
                if(breakFlag==1){
                    printf("\nВы ввели символ %c отличный от цифр!\nПробуйте снова:",CHAR_BREAK_FLAG);
                    res = getPrice();
                    return res;
                }
                printf("\nВы ввели отрицательное значение!\nПробуйте снова:");
                res = getPrice();
                return res;
            } else if(symbol == CHAR_BREAK_FLAG){
                if(breakFlag==1){
                    printf("\nВы ввели символ %c отличный от цифр!\nПробуйте снова:",CHAR_BREAK_FLAG);
                    res = getPrice();
                    return res;
                }
                breakFlag = 1;
            } else{
                printf("\nВы ввели символ %c отличный от цифр!\nПробуйте снова:",symbol);
                res = getPrice();
                return res;
            }
        }
    }
    if(breakFlag){
        return PRICE_BREAK_FLAG;
    }
    res = res + mantis;
    
    return res;
}

void priceIsSave(){
    printf("Цена сохранена!\n");
}

int getCategory(){
    int res = 0;
    int index = 0;
    bool breakFlag = 0;
    printCategories();
    printf("Введите жанр книги:");
    fflush(stdin);
    char symbol = '\0';
    
    while(true){
        scanf("%c", &symbol);
        
        if(symbol == '\n'){
            break;
        }
        
        if(symbol>= ' ' && symbol <= '~'){
            if(symbol >= '0' && symbol <= '9'){
                if(breakFlag==1){
                    printf("\nВы ввели символ %c отличный от цифр!\nПробуйте снова:",CHAR_BREAK_FLAG);
                    res = getPrice();
                    return res;
                }
                res = res*10+(symbol-'0');
                if(res >= categories(numOfCats)){
                    printf("\nЗначение превышает максимальный индекс категории (%d)!\nПробуйте снова:", categories(numOfCats)-1);
                    res = getCategory();
                    return res;
                }
                index++;
            } else if(symbol == '-' && index == 0){
                if(breakFlag==1){
                    printf("\nВы ввели символ %c отличный от цифр!\nПробуйте снова:",CHAR_BREAK_FLAG);
                    res = getPrice();
                    return res;
                }
                printf("\nВы ввели отрицательное значение!\nПробуйте снова:");
                res = getCategory();
                return res;
            } else if(symbol==CHAR_BREAK_FLAG){
                if(breakFlag==1){
                    printf("\nВы ввели символ %c отличный от цифр!\nПробуйте снова:",CHAR_BREAK_FLAG);
                    res = getPrice();
                    return res;
                }
                breakFlag = 1;
            } else{
                printf("\nВы ввели символ %c отличный от цифр!\nПробуйте снова:",symbol);
                res = getCategory();
                return res;
            }
        }
    }
    if(breakFlag){
        return CATEGORY_BREAK_FLAG;
    }
    
    return res;
}

void categoryIsSave(){
    printf("Жанр сохранён!\n");
}

//Функции вывода
void printCategories(){
    printf("\n");
    for(int i = 0; i < categories(numOfCats); i++){
        printf("%d - %s\n", i, categoriesMas[i]);
    }
}

void printBook(BOOK* book){
    printf("\nНазвание: %s\nАвтор: %s", book->title, book->author);
    if(book->year >= 0){
        printf("\nГод издания: %d", book->year);
    } else{
        printf("\nГод издания: %d до н.э.", -book->year);
    }
    if(book->price != 0){
        printf("\nЦена: %.2lf руб.", book->price);
    } else{
        printf("\nЦена: бесплатно!");
    }
    printf("\nЖанр: %s", categoriesMas[book->category]);
}

void printLib(BOOK** books, int booksNum){
    for(int i = 0; i < booksNum; i++){
        printf("\n----------\nКнига №%d", i+1);
        printBook(books[i]);
    }
    printf("\n");
}

void messageDelBook(){
    printf("\nКнига успешно удалена!\n");
}

void messageDelBooks(){
    printf("\nКниги успешно удалены!\n");
}

void putBooksInFile(bookLib* library){
    file = fopen("/Users/timofejovcinnikov/Desktop/Учеба/xcode-labs/lab6/lab6/library.txt", "w");
    if(file!=NULL){
        fprintf(file, "%d\n",library->booksNum);
        for(int i = 0; i < library->booksNum;i++){
            if(i!=library->booksNum){
                fprintf(file, "%s|%s|%d|%.2lf|%d\n",(library->books)[i]->title,(library->books)[i]->author,(library->books)[i]->year,(library->books)[i]->price,(library->books)[i]->category);
            } else{
                fprintf(file, "%s|%s|%d|%.2lf|%d\\",(library->books)[i]->title,(library->books)[i]->author,(library->books)[i]->year,(library->books)[i]->price,(library->books)[i]->category);
            }
        }
    }
    
    printf("\nБиблиотека успешно записана в файл!\n");
    
    fclose(file);
}


void getBooksFromFile(bookLib* library){
    file = fopen("/Users/timofejovcinnikov/Desktop/Учеба/xcode-labs/lab6/lab6/library.txt", "r");
    if(file!=NULL){
        int booksInFile, newSize, oldsize;
        fscanf(file, "%d\n",&booksInFile);
        oldsize = library->booksNum;
        newSize = booksInFile + library->booksNum;
        BOOK** newBooks = new BOOK*[newSize];
        for(int i = 0; i < library->booksNum; i++){
            newBooks[i] = library->books[i];
        }
        delete[] library->books;
        library->books = newBooks;
        library->booksNum = newSize;
        
        for(int k = oldsize; k < library->booksNum; k++){
            library->books[k] = new BOOK;
            bool ifBreak = 0;
            BOOK*& newBook = library->books[k];
            //Название
            int bufForNow = DEFAULT_BUFFER_SIZE, i = 0;
            newBook->title = new char[bufForNow];
            newBook->title[0] = '\0';
            
            char symbol = '\0';
            
            while(true){
                fscanf(file,"%c",&symbol);
                
                if(symbol == FILE_BREAK_SYMBOL){
                    break;
                }
                
                newBook->title[i] = symbol;
                i++;
                if(i > bufForNow-1){
                    bufForNow+=BUFFER_DELTA;
                    char* newDynStr = new char[bufForNow];
                    strCopy(newBook->title, newDynStr);
                    delete[] newBook->title;
                    newBook->title = newDynStr;
                }
            }
            
            //Автор
            bufForNow = DEFAULT_BUFFER_SIZE;
            i = 0;
            newBook->author = new char[bufForNow];
            newBook->author[0] = '\0';
            
            symbol = '\0';
            
            while(true){
                fscanf(file,"%c",&symbol);
                
                if(symbol == FILE_BREAK_SYMBOL || symbol == '\n'){
                    break;
                }
                
                newBook->author[i] = symbol;
                i++;
                if(i > bufForNow-1){
                    bufForNow+=BUFFER_DELTA;
                    char* newDynStr = new char[bufForNow];
                    strCopy(newBook->author, newDynStr);
                    delete[] newBook->author;
                    newBook->title = newDynStr;
                }
            }
            if(ifBreak){
                break;
            }
            
            //Год
            int index = 0;
            bool ifNegative = 0;
            symbol = '\0';
            
            while(true){
                fscanf(file, "%c", &symbol);
                
                if(symbol == FILE_BREAK_SYMBOL || symbol == '\n'){
                    break;
                }
                
                if(symbol >= '0' && symbol <= '9'){
                    newBook->year = newBook->year*10+(symbol-'0');
                    index++;
                } else if(symbol == '-' && index == 0){
                    ifNegative = 1;
                }
            }
            if(ifBreak){
                break;
            }
            
            if(ifNegative){
                newBook->year = -newBook->year;
            }
            
            //Цена
            double mantis = 0;
            bool ifMantis = 0;
            double afterFactor = 1.0;
            symbol = '\0';
            
            while(true){
                fscanf(file, "%c", &symbol);
                
                if(symbol == FILE_BREAK_SYMBOL || symbol == '\n'){
                    break;
                }
                
                if(symbol >= '0' && symbol <= '9'){
                    if(ifMantis){
                        afterFactor*=0.1;
                        mantis = mantis + (symbol-'0')*afterFactor;
                    } else{
                        newBook->price = newBook->price*10+(symbol-'0');
                    }
                } else if(symbol == '.' || symbol == ','){
                    ifMantis = 1;
                }
            }
            newBook->price = newBook->price + mantis;
            //Категория
            int res = 0;
            index = 0;
            symbol = '\0';
            
            while(true){
                fscanf(file, "%c", &symbol);
                
                if(symbol == FILE_BREAK_SYMBOL || symbol == '\n'){
                    break;
                }
                
                if(symbol >= '0' && symbol <= '9'){
                    res = res*10+(symbol-'0');
                    index++;
                }
            }

            
            newBook->category = categories(res);
        }
    } else{
        printf("\nФайла не существует!\n");
    }
    
    printf("\nБиблиотека успешно импортирована из файла!\n");
    
    fclose(file);
}

void printMenu(int numOfBooks){
    if(numOfBooks!=0){
        printf("\nГлавное меню\n----------\nn - ввести новую книгу\nd - удалить книгу\nh - удалить диапазон книг\np - вывести библиотеку\ny - вывести средний год всех книг\ns - войти в меню сортировок\nf - внести библиотеку в файл\nt - импортировать книги из файла\nx - закончить работу\n----------\nВведите команду:");
    } else{
        printf("\nГлавное меню\n----------\nn - ввести новую книгу\n[d] - удалить книгу\n[h] - удалить диапазон книг\n[p] - вывести библиотеку\n[y] - вывести средний год всех книг\n[s] - войти в меню сортировок\n[f] - внести библиотеку в файл\nt - импортировать книги из файла\nx - закончить работу\n----------\nВведите команду:");
    }
}

void printSortMenu(){
    printf("\nМеню сортировок\n----------\nt - сортировка по названию\na - сортировка по автору\ny - сортировка по году\np - сортировка по цене\nc - сортировка по жанру\nb - выйти в главное меню\n----------\nВведите команду:");
}

