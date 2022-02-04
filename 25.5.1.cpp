#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
/*
struct Person {
    std::string name;
    std::string surname;
    int total_cash;
};

struct Payment {
    int payment;
    std::tm date;
    int person_id;
};

void pushStruct(std::vector<Person> &personVct, std::vector<Payment> &paymentVct, const std::string &name, const std::string &surname, int amount, std::tm date){
    int bufferPerson_id = -1;
    for (int i = 0; i < personVct.size(); i++) {
        if (personVct[i].surname == surname and personVct[i].name == name)
            bufferPerson_id = i;
    }
    if (bufferPerson_id == -1){
        personVct.push_back(Person {name, surname, amount});
        bufferPerson_id = personVct.size() - 1;
    }
    else
        personVct[bufferPerson_id].total_cash += amount;
    paymentVct.push_back(Payment {amount, date, bufferPerson_id});
}

void saveAll(const std::vector<Person> &personVct, const std::vector<Payment> &paymentVct, const std::string& fileName = "..\\statement.txt"){
    std::ofstream file (fileName, std::ios::trunc);
    if (file.is_open()) {
        for (const Payment &it: paymentVct)
            file << personVct[it.person_id].name << ' ' << personVct[it.person_id].surname << ' '
                 << it.payment << ' ' << std::put_time(&it.date, "%d.%m.%Y") << std::endl;
        file.close();
    }
    else
        std::cout << "Open file error!" << std::endl;
}

void saveLast(const std::vector<Person> &personVct, const std::vector<Payment> &paymentVct, const std::string& fileName = "..\\statement.txt"){
    std::ofstream file (fileName, std::ios::app);
    if (file.is_open()) {
        Payment it = paymentVct[paymentVct.size() - 1];
        file << personVct[it.person_id].name << ' ' << personVct[it.person_id].surname << ' '
             << it.payment << ' ' << std::put_time(&it.date, "%d.%m.%Y") << std::endl;
        file.close();
    }
    else
        std::cout << "Open file error!" << std::endl;
}

void read(std::vector<Person> &personVct, std::vector<Payment> &paymentVct, const std::string& fileName = "..\\statement.txt") {
    std::ifstream file (fileName);
    if (file.is_open()) {
        while (true) {
            std::string bufferName("Empty"), bufferSurname("Empty");
            std::tm bufferDate{};
            int bufferAmount = 0;
            file >> bufferName >> bufferSurname >> bufferAmount >> std::get_time(&bufferDate, "%d.%m.%Y");
            if (file.eof())
                break;
            pushStruct(personVct, paymentVct, bufferName, bufferSurname, bufferAmount, bufferDate);
        }
        file.close();
    }
    else {
        std::cout << "Open file error!" << std::endl;
    }
}

void add(std::vector<Person> &personVct, std::vector<Payment> &paymentVct) {
    std::string bufferName ("Empty"),bufferSurname ("Empty");
    std::tm bufferDate{};
    int bufferAmount;

    //user interface
    //name
    std::cout << "Enter the name: ";
    std::cin >> bufferName;

    //surname
    std::cout << "Enter the surname: ";
    std::cin >> bufferSurname;

    //payment
    while (true){
        bufferAmount = 0;
        std::cout << "Enter the payment: ";
        std::cin.ignore(32767, '\n');
        std::cin.clear();
        std::cin >> bufferAmount;
        if (std::cin.fail()){
            std::cout << "Error reading payment, try again.\n";
            continue;
        }
        break;
    }

    //date
    while (true){
        std::cout << "Enter the date (dd.mm.yyyy): ";
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cin >> std::get_time(&bufferDate, "%d.%m.%Y");
        if (std::cin.fail()){
            std::cout << "Error reading date, try again.\n";
            continue;
        }
        break;
    }

    //add the data into the structs and file
    pushStruct(personVct, paymentVct, bufferName, bufferSurname, bufferAmount, bufferDate);
    saveLast(personVct, paymentVct);
}

void show (const std::vector<Person> &personVct, const std::vector<Payment> &paymentVct){
    for (const Payment &it: paymentVct)
        std::cout << personVct[it.person_id].name << ' ' << personVct[it.person_id].surname << ' '
             << std::put_time(&it.date, "%d.%m.%Y") << ' ' << it.payment << '\n';
}


int main() {

    std::vector<Person> person;
    std::vector<Payment> payment;

    std::string operationCode; //add or read
    while (true){
        std::cout << R"(Enter command "add" or "read": )";
        std::cin >> operationCode;

        if (std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Entered fault.\n";
            std::cout << "Try again.\n";
            continue;
        }

        for (char &it : operationCode)
            it = tolower(it);
        if (operationCode != "add" and operationCode != "read"){
            std::cin.ignore(32767, '\n');
            std::cout << "Unknown command.\n";
            std::cout << "Try again.\n";
            continue;
        }
        break;
    }

    if (operationCode == "add") {
        read(person, payment);
        add(person, payment);
    }
    else if (operationCode == "read") {
        read(person, payment);
        show(person, payment);
    }


    return 0;
}
*/