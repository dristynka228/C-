#include <iostream>
#include <Windows.h>
using namespace std;

int main() 
{
    setlocale(LC_ALL, "Russian");
    int choice;

    do {
        std::cout << "Выберите действие:\n\n"
            << "1. Сложение\n"
            << "2. Вычитание\n"
            << "3. Частное\n"
            << "4. Произведение\n"
            << "5. Возведение в степень\n"
            << "6. Нахождение квадратного корня\n"
            << "7. Нахождение 1 процента от числа\n"
            << "8. Найти факториал числа\n"
            << "9. Выйти из программы\n\n";

        std::cout << "Введите номер действия: ";
        std::cin >> choice;

        if (choice >= 1 && choice <= 9) {
            double num1, num2, result;

            switch (choice) {
            case 1: 
                std::cout << "Введите первое число: ";
                std::cin >> num1;
                std::cout << "Введите второе число: ";
                std::cin >> num2;
                result = num1 + num2;
                std::cout << "Результат: " << result << std::endl;
                break;

            case 2: 
                std::cout << "Введите первое число: ";
                std::cin >> num1;
                std::cout << "Введите второе число: ";
                std::cin >> num2;
                result = num1 - num2;
                std::cout << "Результат: " << result << std::endl;
                break;

            case 3: 
                std::cout << "Введите делимое: ";
                std::cin >> num1;
                std::cout << "Введите делитель: ";
                std::cin >> num2;
                result = num1 / num2;
                std::cout << "Результат: " << result << std::endl;
                break;

            case 4: 
                std::cout << "Введите первый множитель: ";
                std::cin >> num1;
                std::cout << "Введите второй множитель: ";
                std::cin >> num2;
                result = num1 * num2;
                std::cout << "Результат: " << result << std::endl;
                break;

            case 5: 
                std::cout << "Введите число: ";
                std::cin >> num1;
                std::cout << "Введите степень: ";
                std::cin >> num2;
                result = std::pow(num1, num2);
                std::cout << "Результат: " << result << std::endl;
                break;

            case 6: 
                std::cout << "Введите число: ";
                std::cin >> num1;
                result = std::sqrt(num1);
                std::cout << "Результат: " << result << std::endl;
                break;

            case 7: 
                std::cout << "Введите число: ";
                std::cin >> num1;
                result = num1 / 100;
                std::cout << "1% числа: " << result << std::endl;
                break;

            case 8: 
                std::cout << "Введите число: ";
                std::cin >> num1;

                if (num1 < 0) {
                    std::cout << "Ошибка! Факториал определен только для неотрицательных целых чисел." << std::endl;
                }
                else {
                    result = 1;
                    for (int i = 1; i <= num1; ++i) {
                        result *= i;
                    }
                    std::cout << "Факториал числа " << num1 << ": " << result << std::endl;
                }
                break;

            case 9: 
                std::cout << "До свидания!" << std::endl;
                break;
            }

            std::cout << "\n";
        }
        else {
            std::cout << "Ошибка! Введите действительный номер действия (от 1 до 9).\n\n";
        }

    } while (choice != 9);

    return 0;
}
