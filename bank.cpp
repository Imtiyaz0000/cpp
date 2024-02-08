#include <unordered_map>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

struct Account {
    float bal = 0;
    std::string password;
    std::string name;
    std::string account_name;
};

class Bank {
    private:
        std::unordered_map<int, Account> data;
        int id;
    public:
    Bank() {
        start();
    }

    void start() {
        auto choice;
        std::cout << "\nSelect:\n1.Login\n2.Create Account\n3.Exit\n--> ";
        std::cin >> choice;
        switch (choice) {
            case 1:
            login()
                break;
            case 2:
                create_acc();
                break;
            default:
                std::cout << "\nInvalid input, Retry:\n";
                start();
                break;
        }
    }

    void menu

    void create_acc() {
        std::srand(time(NULL));
        id = rand() % 99999 + 10000;
        Account acc; 
        std::cout << "\nYour id: " << id << endl;
        std::cout << "\nEnter name:\n--> ";
        getline(std::cin, acc.name);
        std::cout << "\nEnter account name:\n--> ";
        getline(std::cin, acc.account_name);
        std::cout << "\nEnter password:\n--> ";
        getline(std::cin, acc.password);
        data.push_back(id, acc);
        std::cout << "\nAccount Created!\nRedirecting...\n";
        menu();
    }
    
    void login() {
        auto temp_id;
        std::string temp_password;
        std::cout << "\nEnter id: (enter 69 to exit)\n--> ";
        std::cin >> temp_id;
        if (temp_id == 69) {start();}
        std::cout << "\nEnter password:\n--> ";
        std::cin >> temp_password;
        if (data[id] == password) {
            id = temp_id;
            std::cout << "\nSuccessfully logged in.\nRedirecting...\n";
            menu();
        }
        else {
            std::cout << "Incorrect id or password, Retry:\n";
            login();
        }
    }
};

int main() {
    Bank();
    return 0;
}
