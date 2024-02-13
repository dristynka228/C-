#include <iostream>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "");
    const int numRows = 3;
    const int numCols = 5;

    float arr[numRows][numCols];

    for (int i = 0; i < numRows; i++) {
        std::cout << "Введите элементы " << (i + 1) << "-й строки (через пробел): ";
        for (int j = 0; j < numCols; j++) {
            std::cin >> arr[i][j];
        }
    }

    for (int i = 0; i < numRows; i++) {
        float sum = 0;
        for (int j = 0; j < numCols; j++) {
            sum += arr[i][j];
        }
        float average = sum / numCols;
        std::cout << "Среднее арифметическое элементов " << (i + 1) << "-й строки: " << average << std::endl;
    }

    return 0;
}
