#include <unordered_map>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <typeinfo>
#include <fstream>
#include <sstream>

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

    bool is_integer(const std::string& str) {
        try {
        std::stoi(str);
        return true;
        }
        catch (const std::invalid_argument&) {return false;}
    }
    bool is_float(const std::string& str) {
        try {
        std::stof(str);
        return true;
        }
        catch (const std::invalid_argument&) {return false;}
    }

    void start() {
        load_data();
        std::string choice;
        std::cout << "\nSelect:\n1.Login\n2.Create Account\n3.Exit\n--> ";
        std::cin >> choice;
        if (!is_integer(choice)) {
            std::cout << "\nInvalid Input, retry:\n";
            start();
        }
        int r_choice = stoi(choice);
        switch (r_choice) {
            case 1:
                login();
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

    void menu() {
        std::string choice;
        int real_choice;
        std::cout << "\nSelect:\n1.check Account Details\n2.Desposit\n3.Withdraw\n4.Transfer Balance\n5.Terminate";
        std::cin >> choice;
        if (!is_integer(choice)) {
            std::cout << "\nInvalid Input, retry:\n";
            menu();
        }
        real_choice = stoi(choice);
        switch (real_choice) {
            case 1:
                check_details();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                transfer();
                break;
            case 5:
                std::cout << "\nTerminating...\n";
                save_data();
                exit(EXIT_SUCCESS);
                break;
            default:
                std::cout << "\nInvalid input, retry: \n";
                menu();
                break;
        }
    }

    void create_acc() {
        std::srand(time(NULL));
        id = rand() % 99999 + 10000;
        if (data.count(id)) {create_acc();}
        Account acc; 
        std::cout << "\nYour id: " << id << std::endl;
        std::cout << "\nEnter name:\n--> ";
        getline(std::cin, acc.name);
        std::cout << "\nEnter account name:\n--> ";
        getline(std::cin, acc.account_name);
        std::cout << "\nEnter password:\n--> ";
        getline(std::cin, acc.password);
        data[id] = acc;
        std::cout << "\nAccount Created!\nRedirecting...\n";
        menu();
    }
    
    void login() {
        std::string temp_id;
        int t_id;
        std::string temp_password;
        std::cout << "\nEnter id: (enter 69 to exit)\n--> ";
        std::cin >> temp_id;
        if (!is_integer(temp_id)) {
            std::cout << "\nInvalid Input, retry:\n";
            login();
        }
        t_id = stoi(temp_id);
        if (t_id == 69) {start();}
        std::cout << "\nEnter password:\n--> ";
        std::cin >> temp_password;
        if (data[t_id].password == temp_password) {
            id = t_id;
            std::cout << "\nSuccessfully logged in.\nRedirecting...\n";
            menu();
        }
        else {
            std::cout << "Incorrect id or password, Retry:\n";
            login();
        }
    }
    void check_details() {
        std::cout << "\nAccount details:\nname: " << data[id].name;
        std::cout << "\naccount name: " << data[id].account_name;
        std::cout << "\nbalance: £" << std::setprecision(2) << std::fixed << data[id].bal << std::endl;
        menu();
    }
    void deposit() {
        std::string amount;
        std::cout << "\nEnter amount to deposit (enter 69 to cancel)\n--> ";
        std::cin >> amount;
        if (!is_float(amount)) {
            std::cout << "\nInvalid Input, retry:\n";
            deposit();
        }
        float am = std::stof(amount);
        if (am == 69) {menu();}
        data[id].bal += am;
        std::cout << "\nDeposit successful!\nRedirecting...\n";
        menu();
    }
    void withdraw() {
        std::string amount;
        std::cout << "\nEnter amount to withdraw (enter 69 to cancel)\n--> ";
        std::cin >> amount;
        if (!is_float(amount)) {
            std::cout << "\nInvalid Input, retry:\n";
            withdraw();
        }
        float am = std::stof(am);
        if (am == 69) {menu();}
        if (data[id].bal < amount) {
            std::cout << "\nInsufficient balance!";
            withdraw();
        }
        data[id].bal -= amount;
        menu();
    }
    void transfer() {
        std::string temp_id, amount;
        std::cout << "\nEnter id to transfer to (enter 69 to cancel)\n--> ";
        std::cin >> temp_id;
        if (!is_integer(temp_id)) {
            std::cout << "\nInvalid Input, retry:\n";
            transfer();
        }
        int t_id = stoi(temp_id);
        if (t_id == 69) {menu();}
        if (!data.count(t_id)) {
            std::cout "\nid not found.\n";
            transfer();
        }
        std::cout << "\nEnter amount to transfer to id: " << t_id << " (enter 'no' to cancel)\n--> ";
        std::cin >> amount;
        if (amount == "no") {menu();}
        if (typeid(amount) != typeid(int)) {
            std::cout << "\nInvalid input, retry:\n";
            transfer();
        }
        if (data[id].bal < amount) {
            std::cout << "\nInsufficent balance!\n";
            transfer();
        }
        data[id].bal -= amount;
        data[t_id].bal += amount;
        std::cout << "Successfully transferred: £" << amount << std::endl;
        menu();
    }
    void load_data() {
        std::ifstream file("data.csv");
        std::string line;
        while (getline(file, line)) {
            std::stringstream ss;
            std::string str_bal, name, acc_name, str_id;
            int real_id;
            float bal;
            Account acc;
            ss << line;
            getline(ss, str_id, ',');
            getline(ss, str_bal, ',');
            getline(ss, name, ',');
            getline(ss, acc_name, ',');
            real_id = stoi(str_id);
            bal = stof(str_bal);
            acc.name = name;
            acc.bal = bal;
            acc.account_name = acc_name;
            data[real_id] = acc;
            file.close();
        }
    }
    void save_data() {
        std::ofstream file("data.csv");
        for (const auto& [key, item]: data) {
            file << key << ',' << item.bal << ',' << item.name << ',' << item.account_name << std::endl;
        }
        file.close();
    }
};

int main() {
    Bank();
    return 0;
}
