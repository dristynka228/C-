#include <iostream>
using namespace std;

     struct Info
    {
        int accountNumber;
        double balance;
        double intrestRate;

        Info(int accountNumber, double balance, double intrestRate)
        {
            this->accountNumber = accountNumber;
            this->balance = 0;
            this->intrestRate = 0;
        }
    };

    class BankAccount {
    private:
        int accountNumber;
        double balance;
        double interestRate;

    public:
        void deposit();
        void withdraw();
        void getBalance();
        void getInterestRate();
        void setInterestRate();
        void getAccountNumber();

        BankAccount(int accountNumber, double balance, double interestRate) {
            this->accountNumber = accountNumber;
            this->balance = 0;
            this->interestRate = 0;
        }

        friend bool transfer(BankAccount& from, BankAccount& to, double amount);
    };

    void BankAccount::deposit() {
        cout << "Ведите номер счета: ";
        cin >> this->accountNumber;
        cout << "Внесите деньги: ";
        cin >> this->balance;
        cout << "Счет открыт!" << endl << endl;
    }

    void BankAccount::withdraw() {
        long long int a;

        do {
            cout << "Сколько надо снять?";
            cin >> a;
            if (a > this->balance) cout << "Недостаточно средств" << endl;
        } while (a > this->balance);
        this->balance -= a;
        cout << "Деньги успешно сняты" << endl;
    }

    void BankAccount::getBalance() {
        cout << "Текущее состояние счета" << endl;
        cout << "Номер счета" << this->accountNumber << endl;
        cout << "Количество средств на счете" << this->balance << endl;
    }

    void BankAccount::getInterestRate() {
        double monthlyInterestRate = 1.0 / 12;
        cout << "Ваша процентная ставка ноль. Ввидите желаемую ставку" << endl;
        cin >> this->interestRate;
        double interestEarned = this->balance * this->interestRate * monthlyInterestRate;
        cout << "Теперь вы будете получать в год: " << interestEarned << endl;
    }

    void BankAccount::setInterestRate() {
        double a = 1.0 / 12;
        int b = 5;
        this->interestRate = this->balance * b * a;
        cout << "Ваша процентная ставка обновлена на 5 и теперь вы получаете: " << this->interestRate << endl;
    }

    void BankAccount::getAccountNumber() {
        cout << "Номер вашей карточки: " << this->accountNumber << endl;
    }

    bool transfer(BankAccount & from, BankAccount & to, double amount) {
        if (amount <= from.balance) {
            from.balance -= amount;
            to.balance += amount;
            std::cout << "Перевод " << amount << " со счета " << from.accountNumber << " на счет " << to.accountNumber << " успешно" << std::endl;
            return true;
        }
        else {
            std::cerr << "Ошибка " << std::endl;
            return false;
        }
    }

    int main() {
        setlocale(LC_ALL, "");

        BankAccount account1(1, 0, 0); // Создаем объект класса BankAccount с номером счета 1, балансом 0 и нулевой процентной ставкой
        BankAccount account2(2, 0, 0); // Создаем второй объект счета

        // Внесение денег на счет
        account1.deposit();

        // Снятие денег со счета
        account1.withdraw();

        // Получение баланса
        account1.getBalance();

        // Получение процентной ставки
        account1.getInterestRate();

        // Установка процентной ставки
        account1.setInterestRate();

        // Получение номера счета
        account1.getAccountNumber();

        double amount = 100.0; // Сумма для перевода
        if (transfer(account1, account2, amount)) {
            cout << "Перевод прошел успешно!" << endl;
        }
        else {
            cout << "Не удалось выполнить перевод." << endl;
        }

        return 0;
    }