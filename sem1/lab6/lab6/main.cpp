#include <cstdio>
#include <iostream>
#include "Helping.h"
#include "InAndOut.hpp"
#include "Book.hpp"
#include "LibraryStruct.hpp"
#include "Sorting.hpp"

/*
 
 Тестировочная библиотека в файл
 
 Y test book|O test book|4|123.00|6
 E test book|P test book|-333|44444.00|1
 EbO test bok|W test book|0|321312312.00|4
 J test book|44|-2999|38.00|7
 lpo test book|ggggg|400|2023.00|3
 
 */

int main(){
    setlocale(LC_ALL, "Russian");
    
    bool keepGoing = 1;
    bookLib* library = new bookLib;
    
    char symbol;
    char enter;
    char sortSym;
    
    while(keepGoing){
        printMenu(library->booksNum);
        fflush(stdin);
        scanf("%c", &symbol);
        if(symbol == '\n'){
            printf("\nВы ничего не ввели! Попробуйте снова:\n");
            continue;
        }
        scanf("%c", &enter);
        if(enter != '\n'){
            printf("\nВы ввели больше одного символа! Попробуйте снова:\n");
            continue;
        }
        
        if(symbol>= ' ' && symbol <= '~'){
            if(library->booksNum!=0){
                switch (symbol) {
                    case 'n':
                        library->addNewBook();
                        break;
                    case 'd':
                        library->deleteBook();
                        break;
                    case 'h':
                        library->deleteDiapBooks();
                        break;
                    case 'p':
                        library->printBooksLib();
                        break;
                    case 'y':
                        library->countAvYear();
                        if(library->avYear >= 0){
                            printf("\nCредний год всех книг: %lf\n", library->avYear);
                        } else{
                            printf("\nCредний год всех книг: %lf до н.э.\n", -library->avYear);
                        }
                        break;
                    case 's':
                        while(true){
                            printSortMenu();
                            fflush(stdin);
                            scanf("%c", &sortSym);
                            bool ifLeave = 1;
                            switch (sortSym) {
                                case 'a':
                                    sortAuthor(library);
                                    library->printBooksLib();
                                    printf("\nБиблиотека успешно отсортирована по автору!\n");
                                    break;
                                case 't':
                                    sortTitle(library);
                                    library->printBooksLib();
                                    printf("\nБиблиотека успешно отсортирована по названию!\n");
                                    break;
                                case 'y':
                                    sortYear(library);
                                    library->printBooksLib();
                                    printf("\nБиблиотека успешно отсортирована по году!\n");
                                    break;
                                case 'p':
                                    sortPrice(library);
                                    library->printBooksLib();
                                    printf("\nБиблиотека успешно отсортирована по цене!\n");
                                    break;
                                case 'c':
                                    sortCategory(library);
                                    library->printBooksLib();
                                    printf("\nБиблиотека успешно отсортирована по жанру!\n");
                                    break;
                                case 'b':
                                    break;
                                default:
                                    ifLeave = 0;
                                    printf("Вы ввели неправильный символ команды:%c!\nПопробуйте снова:", sortSym);
                                    break;
                            }
                            if(ifLeave){
                                break;
                            }
                        }
                        break;
                    case 'f':
                        putBooksInFile(library);
                        break;
                    case 't':
                        getBooksFromFile(library);
                        library->printBooksLib();
                        break;
                    case 'x':
                        keepGoing = 0;
                        break;
                    default:
                        printf("\nВы ввели неправильный символ команды:%c!\nПопробуйте снова:", symbol);
                        break;
                }
            } else{
                switch (symbol) {
                    case 'n':
                        library->addNewBook();
                        break;
                    case 'd':
                    case 'h':
                    case 'p':
                    case 'y':
                    case 's':
                    case 'f':
                        printf("\nЭто действие нельзя совершить при пустой библиотеке! Добавьте книги и попробуйте снова!\n");
                        break;
                    case 't':
                        getBooksFromFile(library);
                        library->printBooksLib();
                        break;
                    case 'x':
                        keepGoing = 0;
                        break;
                    default:
                        printf("\nВы ввели неправильный символ команды:%c!\nПопробуйте снова:", symbol);
                        break;
                }
            }
        }
    }
    delete library;
    
    char ending;
    printf("\nВведите любое значение, чтобы закончить программу:");
    fflush(stdin);
    scanf("%c",&ending);
    return 0;
}
