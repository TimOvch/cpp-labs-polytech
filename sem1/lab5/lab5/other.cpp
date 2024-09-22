#include "other.hpp"
#include <iostream>
#include <string>
///////////////////////////////////////////////////

//функции для калькулятора
double Sum(double a, double b){
    return a+b;
}

double Sub(double a, double b){
    return a-b;
}

double Mul(double a, double b){
    return a*b;
}

double Div(double a, double b){
    return a/b;
}

//функции для сортировки
void SwapInt(void* p1, void* p2)
{
    int temp = *(static_cast<int*>(p1));
    *(static_cast<int*>(p1))=*(static_cast<int*>(p2));
    *(static_cast<int*>(p2))=temp;
}

void SwapDouble(void* p1, void* p2)
{
    double temp = *(static_cast<double*>(p1));
    *(static_cast<double*>(p1))=*(static_cast<double*>(p2));
    *(static_cast<double*>(p2))=temp;
}

void SwapStr(void* p1, void* p2)
{
    char** str1 = static_cast<char**>(p1);
    char** str2 = static_cast<char**>(p2);
    
    char* temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

int CmpInt(void* p1, void* p2)
{
    int nResult;
    int a = *(static_cast<int*>(p1));
    int b = *(static_cast<int*>(p2));
    if(a<b){
        nResult = -1;
    } else if(a==b){
        nResult = 0;
    } else {
        nResult = 1;
    }
    return  nResult;
}

int CmpDouble(void* p1, void* p2)
{
    int nResult;
    double a = *(static_cast<double*>(p1));
    double b = *(static_cast<double*>(p2));
    if(a<b){
        nResult = -1;
    } else if(a==b){
        nResult = 0;
    } else {
        nResult = 1;
    }
    return  nResult;
}

int CmpStr(void* p1, void* p2)
{
    char* a = *static_cast<char**>(p1);
    char* b = *static_cast<char**>(p2);
    
    int i = 0;
    while (*(a+i) == *(b+i)){
            if (*a == '\0') {
                return 0;
            }
        i++;
        }
    
    return *(a+i)-*(b+i);
}

void Sort(char* pcFirst, int nNumber, int size,
     void (*Swap)(void*, void*), int (*Compare)(void*, void*) )
{
    int i;
    for(i=1; i<nNumber; i++)
        for(int j=nNumber-1; j>=i; j--)
        {
            char* pCurrent = pcFirst+j*size;
            char* pPrevious = pcFirst+(j-1)*size;
            if((*Compare)( pPrevious, pCurrent ) > 0)//требуется переставить
                (*Swap)( pPrevious, pCurrent );
        }
}

// Функции для 3 задания

const char* GetString1(){
    return "Get String 1";
}
const char* GetString2(){
    return "Get String 2";
}
const char* GetString3(){
    return "Get String 3";
}
const char* GetString4(){
    return "Get String 4";
}

//фунции для BOOK

const char* categoryStrings[] = {"romantic","drama","detecive","classic","scientific"};

void printBook(BOOK* a){
    line();
    printf("Title: %s\nAuthor: %s\nYear: %d\nPrice: %.2f\nCategory: %s",a->title,a->author,a->year, a->price,categoryStrings[a->category]);
    line();
}

void initBook(BOOK* a){
    char bookTitle[MAX_LEN];
    printf("Enter Book Title:");
    fflush(stdin);
    scanf("%s",bookTitle);
    a->EnterTitle(bookTitle);
    printf("\n");
    
    char bookAuthor[MAX_LEN];
    printf("Enter Book Author:");
    fflush(stdin);
    scanf("%s",bookAuthor);
    a->EnterAuthor(bookAuthor);
    printf("\n");
    
    int bookYear;
    printf("Enter Book Year:");
    scanf("%d",&bookYear);
    if(bookYear < PismYear || bookYear > 2023){
        while(true){
            printf("Wrong year, enter again: ");
            scanf("%d",&bookYear);
            if(bookYear < PismYear || bookYear > 2023){
                continue;
            } else{
                break;
            }
        }
    }
    a->year = bookYear;
    printf("\n");
    
    double bookPrice;
    printf("Enter Book Price:");
    scanf("%lf",&bookPrice);
    if(bookPrice<0){
        while(true){
            printf("Price can't be negative, enter again: ");
            scanf("%lf",&bookPrice);
            if(bookPrice<0){
                continue;
            } else{
                break;
            }
        }
    }
    a->price = bookPrice;
    printf("\n");
    
    printf("Book categories:\n0 - romantic\n1 - drama\n2 - detective\n3 - classic\n4 - scientific\n");
    int tempCat;
    categories bookCategory;
    printf("Enter Book Category:");
    scanf("%d",&tempCat);
    if(tempCat>4 || tempCat<0){
        while(true){
            printf("Wrong category, enter again: ");
            scanf("%d",&tempCat);
            if(tempCat>4 || tempCat<0){
                continue;
            } else{
                break;
            }
        }
    }
    bookCategory = (categories)tempCat;
    a->category=bookCategory;
    printf("\n");
}

//Доп функции

void line(){
    printf("\n--------------------------------\n");
}

void printArray(const int* arr, const int size){
    for (int i = 0; i < size; i++) {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void printArray(const double* arr, const int size){
    for (int i = 0; i < size; i++) {
        printf("%.1lf ",arr[i]);
    }
    printf("\n");
}

void printArray(char** arr, const int size){
    for (int i = 0; i < size; i++) {
        printf("%s ",arr[i]);
    }
    printf("\n");
}
