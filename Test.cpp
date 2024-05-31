#include <iostream>
#include <locale>
#include <Windows.h>
using namespace std;

typedef bool(*CharSearchFunction)(const char*, const char*);

int main() {
    setlocale(LC_ALL, "");
    HINSTANCE hinstLib;
    CharSearchFunction CharSearch;
    
    char inputString[100];
    char inputChars[10];
    cout << "Введите строку: ";
    cin.getline(inputString, 100);
    cout << "Введите символы для поиска: ";
    cin.getline(inputChars, 10); 

    hinstLib = LoadLibrary(TEXT("BOMBA.dll"));
    if (hinstLib != NULL) {
        
        CharSearch = (CharSearchFunction)GetProcAddress(hinstLib, "CharSearch");
        if (NULL != CharSearch) {
          
            bool result = CharSearch(inputString, inputChars);
            if (result) {
                cout << "буковка/слово найдено!!" << endl;
            }
            else {
                cout << "буковка/слово не найдено:(" << endl;
            }
        }
        
        FreeLibrary(hinstLib);
    }
    return 0;
}