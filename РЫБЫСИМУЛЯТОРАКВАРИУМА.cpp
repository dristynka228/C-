
#include <iostream>
#include <vector>

class Aquarium {
public:
    int volume;
    int numFish;
    int numPlants;
    int numDecorations;

    Aquarium(int volume) : volume(volume), numFish(0), numPlants(0), numDecorations(0) {}

    void sellAquarium() {
        std::cout << "АКВАРИУМ ПРОДАН, ПОСХАЛКО ПОСХАЛКО ВКЛЮЧАЙТЕ ВЕНТИЛЯТОРЫ" << std::endl;
        numFish = 0;
        numPlants = 0;
        numDecorations = 0;
    }

    void cleanAquarium() {
        std::cout << "Аквариум очищен." << std::endl;
    }

    void removeDeadFish() {
        std::cout << "Мертвые рыбы выкинуты." << std::endl;
        numFish--;
    }
};

class Fish {
public:
    std::string name;
    int age;
    int stepsUntilDeath;
    int stepsUntilReproduce;

    Fish(std::string name, int age, int stepsUntilDeath, int stepsUntilReproduce) : name(name), age(age), stepsUntilDeath(stepsUntilDeath), stepsUntilReproduce(stepsUntilReproduce) {}

    void feedFish() {
        std::cout << "Рыбка " << name << " накормлена." << std::endl;
        stepsUntilDeath += 10;
        stepsUntilReproduce -= 5;
    }

    void addFish() {
        std::cout << "аааааа рыба в аквариуме" << std::endl;
    }

    bool isAlive() {
        return stepsUntilDeath > 0;
    }
};

class Plant {
public:
    std::string type;
    int height;

    Plant(std::string type, int height) : type(type), height(height) {}

    void plantNewPlant() {
        std::cout << "Новое растение посажено." << std::endl;
    }

    void trimPlant() {
        std::cout << "Растение подстрижено." << std::endl;
        height /= 2;
    }
};

class Decoration {
public:
    std::string type;
    int amount;

    Decoration(std::string type, int amount) : type(type), amount(amount) {}

    void decorationNewdecoration() {
        std::cout << "добавлен новый кусок говна из пластика" << std::endl;
    }

    void decorationDeletedecoration() {
        std::cout << "вы убрали кусок кластика из аквариума" << std::endl;
        amount --;
    }
};

void interaction(Fish& fish, Plant& plant) {
    if (fish.isAlive()) {
        if (plant.height > 0) {
            std::cout << "Рыбка " << fish.name << " съела водоросль." << std::endl;
            plant.height = plant.height / 2;
            fish.stepsUntilDeath += 2;
            fish.stepsUntilReproduce -= 2;
        }
        else {
            std::cout << "Рыбка " << fish.name << " умерла от голода." << std::endl;
            fish.stepsUntilDeath = 0;
        }
    }
}

void eventHandler(Aquarium& aquarium, Fish& fish, Plant& plant) {
    if (!fish.isAlive()) {
        aquarium.removeDeadFish();
    }

    if (fish.stepsUntilReproduce <= 0) {
        std::cout << "Рыбка " << fish.name << " размножилась." << std::endl;
        aquarium.numFish++;
        fish.stepsUntilReproduce = 10;
    }

    interaction(fish, plant);
}

void displayAquariumStatus(Aquarium& aquarium, Fish& fish, Plant& plant, Decoration& decoration) {
    std::cout << "Текущее состояние аквариума:" << std::endl;
    std::cout << "Количество рыб: " << aquarium.numFish << std::endl;
    std::cout << "Количество растений: " << aquarium.numPlants << std::endl;
    std::cout << "Количество украшений: " << aquarium.numDecorations << std::endl;
    std::cout << "Название украшения: " << decoration.type << std::endl;

    std::cout << "Состояние рыб:" << std::endl;
    std::cout << "Имя: " << fish.name << std::endl;
    std::cout << "Возраст: " << fish.age << std::endl;
    std::cout << "Шаги до смерти: " << fish.stepsUntilDeath << std::endl;
    std::cout << "Шаги до размножения: " << fish.stepsUntilReproduce << std::endl;

    std::cout << "Состояние растения:" << std::endl;
    std::cout << "Тип: " << plant.type << std::endl;
    std::cout << "Высота: " << plant.height << std::endl;
}

int main() {
    setlocale(LC_ALL, "");
    Aquarium aquarium(100);
    Fish fish("ГУППИ", 1, 100, 50);
    Plant plant("Элодея", 10000);
    Decoration decoration("Монастырь", 2);

        int choice;
    do {
        std::cout << "Выберите действие:" << std::endl;
        std::cout << "1. Покормить рыб" << std::endl;
        std::cout << "2. Посадить новые растения" << std::endl;
        std::cout << "3. Подстричь растения" << std::endl;
        std::cout << "4. Добавить декорацию" << std::endl;
        std::cout << "5. Убрать декорацию" << std::endl;
        std::cout << "6. Продать аквариум" << std::endl;
        std::cout << "7. Очистить аквариум" << std::endl;
        std::cout << "8. Вывести текущее состояние аквариума" << std::endl;
        std::cout << "9. ДОБАВИТЬ РЫБУ В АКВАРИУМ" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cin >> choice;

        switch (choice) {
        case 1:
            fish.feedFish();
            break;
        case 2:
            plant.plantNewPlant();
            aquarium.numPlants++;
            break;
        case 3:
            plant.trimPlant();
            break;
        case 4:
            decoration.decorationNewdecoration();
            aquarium.numDecorations++;
            break;
        case 5:
            decoration.decorationDeletedecoration();
            break;
        case 6:
            aquarium.sellAquarium();
            return 0;
            break;
        case 7:
            aquarium.cleanAquarium();
            break;
        case 8:
            displayAquariumStatus(aquarium, fish, plant, decoration);
            break;
        case 9:
            fish.addFish();
            aquarium.numFish++;
        }

        eventHandler(aquarium, fish, plant);

    } while (choice != 0);

    return 0;
}
