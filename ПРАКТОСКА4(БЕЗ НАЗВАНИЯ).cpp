#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <locale.h>


std::string reverse(const std::string& word) {
    std::string reversedWord = word;
    std::reverse(reversedWord.begin(), reversedWord.end());
    return reversedWord;
}

std::string removeVowels(const std::string& word) {
    std::string withoutVowels = "";
    for (char c : word) {
        if (c != 'e' && c != 'y' && c != 'u' && c != 'i' && c != 'o' &&
            c != 'a') {
            withoutVowels += c;
        }
    }
    return withoutVowels;
}

std::string removeConsonants(const std::string& word) {
    std::string withoutConsonants = "";
    for (char c : word) {
        if (c != 'q' && c != 'w' && c != 'r' && c != 't' && c != 'p' &&
            c != 's' && c != 'd' && c != 'f' && c != 'g' && c != 'h' &&
            c != 'j' && c != 'k' && c != 'l' && c != 'z' && c != 'x' &&
            c != 'c' && c != 'v' && c != 'b' && c != 'n' && c != 'm'){

            withoutConsonants += c;
        }
    }
    return withoutConsonants;
}

std::string shuffle(const std::string& word) {
    std::string shuffledWord = word;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(shuffledWord.begin(), shuffledWord.end(), std::default_random_engine(seed));
    return shuffledWord;
}

int main() {
    setlocale(LC_ALL, "");
    std::cout << "Введите слово: ";
    std::string word;
    std::cin >> word;

    int choice;
    std::cout << "Выберите действие:" << std::endl;
    std::cout << "1. Слово выводится задом наперед" << std::endl;
    std::cout << "2. Вывести слово без гласных" << std::endl;
    std::cout << "3. Вывести слово без согласных" << std::endl;
    std::cout << "4. Рандомно раскидывать буквы заданного слова" << std::endl;
    std::cin >> choice;

    switch (choice) {
    case 1:
        std::cout << "Результат: " << reverse(word) << std::endl;
        break;
    case 2:
        std::cout << "Результат: " << removeVowels(word) << std::endl;
        break;
    case 3:
        std::cout << "Результат: " << removeConsonants(word) << std::endl;
        break;
    case 4:
        std::cout << "Результат: " << shuffle(word) << std::endl;
        break;
    default:
        std::cout << "Неверный выбор." << std::endl;
        break;
    }

    return 0;
}
