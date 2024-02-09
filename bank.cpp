#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <typeinfo>
#include <unordered_map>

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

  bool is_integer(const std::string &str) {
    try {
      std::stoi(str);
      return true;
    } catch (const std::invalid_argument &) {
      return false;
    }
  }
  bool is_float(const std::string &str) {
    try {
      std::stof(str);
      return true;
    } catch (const std::invalid_argument &) {
      return false;
    }
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
    case 3:
      std::cout << "\nTerminating...\n";
      save_data();
      exit(EXIT_SUCCESS);
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
    std::cout << "\nSelect:\n1.check Account Details\n2.Desposit\n3.Withdraw\n4.Transfer Balance\n5.Logout\n6.Delete account\n7.Terminate\n--> ";
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
      start();
    case 6:
      delete_acc();
      break;
    case 7:
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
    if (data.count(id)) {
      create_acc();
    }
    Account acc;
    std::cout << "\nYour id: " << id << std::endl;
    std::cout << "\nEnter name:\n--> ";
    std::cin.ignore();
    getline(std::cin, acc.name);
    std::cout << "\nEnter account name:\n--> ";
    getline(std::cin, acc.account_name);
    std::cout << "\nEnter password:\n--> ";
    getline(std::cin, acc.password);
    data[id] = acc;
    std::cout << "\nAccount Created!\nRedirecting...\n";
    menu();
  }
  void delete_acc() {
    std::string choice;
    std::cout << "\nAre you sure?(yes/no)(make sure to transfer and withdraw your money)\n--> ";
    std::cin >> choice;
    if (choice == "no") {
      menu();
    } else if (choice == "yes") {
      data.erase(id);
      std::cout << "\nAccount successfully deleted!\n";
      start();
    } else {
      std::cout << "\nInvalid input, retry\n";
      menu();
    }
  }

  void login() {
    std::string temp_id;
    std::string temp_password;
    std::cout << "\nEnter id: (enter 69 to exit)\n--> ";
    std::cin >> temp_id;
    if (!is_integer(temp_id)) {
      std::cout << "\nInvalid Input, retry:\n";
      login();
    }
    int t_id = stoi(temp_id);
    if (t_id == 69) {
      start();
    }
    std::cout << "\nEnter password:\n--> ";
    std::cin >> temp_password;
    if (data[t_id].password == temp_password) {
      id = t_id;
      std::cout << "\nSuccessfully logged in.\nRedirecting...\n";
      menu();
    } else {
      std::cout << "Incorrect id or password, Retry:\n";
      login();
    }
  }
  void check_details() {
    std::cout << "\nid: " << id;
    std::cout << "\nAccount details:\nname: " << data[id].name;
    std::cout << "\naccount name: " << data[id].account_name;
    std::cout << "\nbalance: " << std::setprecision(2) << std::fixed << data[id].bal << " pounds" << std::endl;
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
    if (am == 69) {
      menu();
    }
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
    float am = std::stof(amount);
    if (am == 69) {
      menu();
    }
    if (data[id].bal < am) {
      std::cout << "\nInsufficient balance!";
      withdraw();
    }
    data[id].bal -= am;
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
    if (t_id == 69) {
      menu();
    }
    if (!data.count(t_id)) {
      std::cout << "\nid not found.\n";
      transfer();
    }
    std::cout << "\nEnter amount to transfer to id: " << t_id << " (enter 'no' to cancel)\n--> ";
    std::cin >> amount;
    if (amount == "no") {
      menu();
    }
    if (!is_float(amount)) {
      std::cout << "\nInvalid Input, retry:\n";
      transfer();
    }
    float am = std::stof(amount);
    if (data[id].bal < am) {
      std::cout << "\nInsufficent balance!\n";
      transfer();
    }
    data[id].bal -= am;
    data[t_id].bal += am;
    std::cout << "Successfully transferred: £" << amount << std::endl;
    menu();
  }
  void load_data() {
    std::ifstream file("data.csv");
    std::string line;
    while (getline(file, line)) {
      std::stringstream ss;
      std::string str_bal, name, acc_name, str_id, pass;
      int real_id;
      float bal;
      Account acc;
      ss << line;
      getline(ss, str_id, ',');
      getline(ss, str_bal, ',');
      getline(ss, name, ',');
      getline(ss, acc_name, ',');
      getline(ss, pass, ',');
      real_id = stoi(str_id);
      bal = stof(str_bal);
      acc.name = name;
      acc.bal = bal;
      acc.account_name = acc_name;
      acc.password = pass;
      data[real_id] = acc;
      file.close();
    }
  }
  void save_data() {
    std::ofstream file("data.csv", std::ios::out);
    for (const auto &item : data) {
      file << item.first << ',' << item.second.bal << ',' << item.second.name << ',' << item.second.account_name << ',' << item.second.password << std::endl;
    }
    file.close();
  }
};

int main() {
  Bank();
  return 0;
}
