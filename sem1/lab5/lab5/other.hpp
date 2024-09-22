//Функции для калькулятора

double Sum(double a, double b);
double Sub(double a, double b);
double Mul(double a, double b);
double Div(double a, double b);

//Функции для сортировки

void Sort(char* pcFirst, int nNumber, int size,
          void (*Swap)(void*, void*), int (*Compare)(void*, void*) );
void Sort(char** pcFirst, int nNumber, int size,
          void (*Swap)(void*, void*), int (*Compare)(void*, void*));
void SwapInt(void* p1, void* p2);
void SwapDouble(void* p1, void* p2);
void SwapStr(void* p1, void* p2);
int CmpInt(void* p1, void* p2);
int CmpDouble(void* p1, void* p2);
int CmpStr(void* p1, void* p2);

//3 задание

const char* GetString1();
const char* GetString2();
const char* GetString3();
const char* GetString4();

//BOOK

#define MAX_LEN 100
#define PismYear -5000

enum categories{
    romantic,
    drama,
    detecive,
    classic,
    scientific
};

struct BOOK{
    char author[MAX_LEN];
    char title[MAX_LEN];
    int year;
    double price;
    categories category;
    
    void EnterAuthor(const char* input){
        int i = 0;
        while(input[i] != '\0'){
            author[i] = input[i];
            i++;
        }
        author[MAX_LEN-1] = '\0';
    }
    
    void EnterTitle(const char* input){
        int i = 0;
        while(input[i] != '\0'){
            title[i] = input[i];
            i++;
        }
        title[MAX_LEN-1] = '\0';
    }
};

void printBook(BOOK* a);

void initBook(BOOK* a);

//Доп функции
void printArray(const int* arr, const int size);
void printArray(const double* arr, const int size);
void printArray(char** arr, const int size);
void line();
