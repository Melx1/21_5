#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <iomanip>
#include <utility>
#include <fstream>

struct Person {
    std::string name;
    int lives{}, armor{}, damage{};
    int group{}; // 1 - player, 2 - enemy
    std::pair<int, int> position; // (0, 0) <= (x, y) <= (39, 39)

    friend std::ostream& operator<< (std::ostream &out, const Person &person);
};

//Person functions
Person createRandPerson (const std::string &name, std::mt19937 &generator);
Person createPerson ();
std::ostream& operator << (std::ostream &out, const Person &person);
void savePerson(std::ofstream & file, const Person &person);
Person loadPerson(std::ifstream & file);


//general purpose functions
template <typename T>
void input (T &buffer);
int getRandomNumber(std::mt19937 &generator, const int &min, const int &max);
std::pair<int, int> operator + (const std::pair<int, int> &firstPair, const std::pair<int, int> &secondPair);
std::pair<int, int> &operator += (std::pair<int, int> &firstPair, const std::pair<int, int> &secondPair);

//general game functions
void drawField (const std::vector<Person> &poolPersons);
void putRandomPositions (std::vector<Person>& poolPersons, std::mt19937 &generator);
void drawPersons (const std::vector<Person> &poolPersons);
int  move (std::vector<Person> &poolPersons, Person & personRef, const std::pair<int, int> &shift);
void fight (std::vector<Person> &poolPersons, Person & personRef, int target);
void randomEnemiesTurn (std::vector<Person> &poolPersons, std::mt19937 &generator);
void playerTurn(std::vector<Person> &poolPersons);
bool save (const std::string &fileName, const std::vector<Person> &poolPersons);
bool load (const std::string &fileName, std::vector<Person> &poolPersons);



int main() {
    std::mt19937 rand;
    rand.seed(static_cast<unsigned int>(time(nullptr)));

    std::vector<Person> poolPersons;

    //generation new game
    for (int i = 0; i < 5; ++i) {
        poolPersons.push_back(createRandPerson( "Enemy #" + std::to_string(i+1), rand));
    }
    poolPersons.push_back(createPerson());
    putRandomPositions(poolPersons, rand);
    bool isPlayerAlive = true;
    drawField(poolPersons);
    drawPersons(poolPersons);


    //game
    while (poolPersons.size() > 1 and isPlayerAlive) {
        playerTurn(poolPersons);
        randomEnemiesTurn(poolPersons, rand);
        if (poolPersons.back().group != 1) {
            isPlayerAlive = false;
        }
        drawField(poolPersons);
        drawPersons(poolPersons);
    }

    if (isPlayerAlive)
        std::cout << std::endl << "You win!";
    else
        std::cout << std::endl << "You loose!";

    return 0;
}


Person createRandPerson (const std::string &name, std::mt19937 &generator){
    Person result{};
    result.name   = name;
    result.lives  = getRandomNumber(generator, 50, 150);
    result.armor  = getRandomNumber(generator, 0,  50);
    result.damage = getRandomNumber(generator, 15, 30);

    result.group  = 2;
    //position is assigned during the game
    result.position.first  = 0;
    result.position.second = 0;

    return result;
}

Person createPerson (){
    Person result;

    std::cout << "Enter character name:";
    input(result.name);

    std::cout << "Enter character lives:";
    input(result.lives);

    std::cout << "Enter character armor:";
    input(result.armor);

    std::cout << "Enter character damage:";
    input(result.damage);

    result.group  = 1;
    //position is assigned during the game
    result.position.first  = 0;
    result.position.second = 0;

    return result;
}

std::ostream& operator << (std::ostream &out, const Person &person){
    out << person.name << ":"
        << " lives=" << std::setw(3) << person.lives
        << " armor="  << std::setw(3) << person.armor
        << " damage=" << std::setw(3) << person.damage
        << " position =" << std::setw(2) << person.position.first << ',' << std::setw(2) << person.position.second;
    return out;
}

void savePerson(std::ofstream & file, const Person &person){
    int len = person.name.length();
    file << len << ' ';
    file.write(person.name.c_str(), len) ;
    file << person.lives << ' ' << person.armor << ' ' << person.damage << ' '
         << person.group << ' ' << person.position.first << ' ' << person.position.second << std::endl;
}

Person loadPerson(std::ifstream & file){
    Person person;
    int len;
    file >> len;
    person.name.resize(len+1);
    file.read((char*)person.name.c_str(), len+1);
    file >> person.lives >> person.armor >> person.damage
         >> person.group >> person.position.first >> person.position.second;
    return person;
}


template <typename T>
void input (T &buffer) {
    while (true) {
        std::cin.rdbuf()->pubsync();
        std::cin.clear();
        std::cin >> buffer;
        if (std::cin.fail()) {
            std::cout << "Entered error. Try again:";
            continue;
        }
        return;
    }
}

int getRandomNumber(std::mt19937 &generator, const int &min, const int &max) {
    int minValue = min, maxValue = max;

    if (minValue > maxValue)
        std::swap(minValue,maxValue);

    std::uniform_int_distribution<int> distribution(minValue, maxValue);

    return distribution(generator);
}

std::pair<int, int> operator + (const std::pair<int, int> &firstPair, const std::pair<int, int> &secondPair){
    return std::pair<int, int> {firstPair.first + secondPair.first, firstPair.second + secondPair.second};
}

std::pair<int, int> & operator += (std::pair<int, int> &firstPair, const std::pair<int, int> &secondPair){
    firstPair.first = firstPair.first + secondPair.first;
    firstPair.second = firstPair.second + secondPair.second;
    return firstPair;
}


void drawField (const std::vector<Person> &poolPersons){
    std::cout << std::endl;

    for (int i = 0; i < 40; ++i){
        for (int j = 0; j < 40; j++){
            bool isEmpty = true;

            for (const auto & it: poolPersons){
                if (it.position.first == j and it.position.second == i){
                    if (it.group == 1)
                        std::cout << 'P';
                    else if (it.group == 2)
                        std::cout << 'E';
                    isEmpty = false;
                    break;
                }
            }

            if (isEmpty)
                std::cout << '.';

            std::cout << ' ';
        }
        std::cout << std::endl;
    }
}

void putRandomPositions (std::vector<Person> &poolPersons, std::mt19937 &generator){
    //generate
    for (auto &it: poolPersons){
        it.position.first  = getRandomNumber(generator, 0, 39);
        it.position.second = getRandomNumber(generator, 0, 39);
    }

    //check equal positions
    for (auto it = poolPersons.begin() + 1; it != poolPersons.end(); ++it) {
        if (it->position == (it - 1)->position){
            it->position.first  = getRandomNumber(generator, 0, 39);
            it->position.second = getRandomNumber(generator, 0, 39);
            --it;
        }
    }
}

void drawPersons (const std::vector<Person> &poolPersons) {
    std::cout << std::endl;
    for (auto &it: poolPersons){
        std::cout << it << std::endl;
    }
}

int move (std::vector<Person> &poolPersons, Person &personRef, const std::pair<int, int> &shift){
    //-1 - move ok, -2 - limit of field, 0 and more - reference of the another person on the way
    std::pair<int, int> newPosition;
    newPosition = personRef.position + shift;

    if (newPosition.first < 0 or newPosition.first >= 40 or newPosition.second < 0 or newPosition.second >= 40){
        return -2;
    }

    for (int i = 0; i < poolPersons.size(); ++i){
        if (newPosition == poolPersons[i].position and personRef.name != poolPersons[i].name){
            return i;
        }
    }

    personRef.position = newPosition;
    return -1;
}

void fight (std::vector<Person> &poolPersons, Person &personRef, int target){
    //friendly fire off
    if (poolPersons[target].group == personRef.group)
        return;

    std::cout << std::endl << personRef.name << " damage " << poolPersons[target].name;
    poolPersons[target].armor -= personRef.damage;
    if (poolPersons[target].armor < 0){
        poolPersons[target].lives += poolPersons[target].armor;
        poolPersons[target].armor = 0;
    }

    if (poolPersons[target].lives <= 0){
        poolPersons.erase (poolPersons.begin() + target);
        std::cout << std::endl << "Enemy #" << target + 1 << " died";
    }
}

void randomEnemiesTurn (std::vector<Person> &poolPersons, std::mt19937 &generator) {
    for (auto &it : poolPersons){
        if (it.group == 2) {
            std::pair<int, int> shift;
            shift.first = getRandomNumber(generator, -1, 1);
            if (shift.first == 0)
                shift.second = getRandomNumber(generator, -1, 1);
            else
                shift.second = 0;

            //equalize the chances of x move and y move
            if (getRandomNumber(generator, 0, 1) > 0){
                std::swap(shift.first, shift.second);
            }

            int target = move(poolPersons, it, shift);
            if (target >= 0)
                fight(poolPersons, it, target);
        }
    }
}

void playerTurn(std::vector<Person> &poolPersons){
    while (true){
        std::string bufferStr;
        std::cout << "Enter left(l)/right(r)/top(t)/bottom(b) to move or save/load the game:";
        input(bufferStr);

        //save & load
        if (bufferStr == "save") {
            save("..\\save.bin", poolPersons);
            continue;
        }
        if (bufferStr == "load") {
            if (load("..\\save.bin", poolPersons)){
                drawField(poolPersons);
                drawPersons(poolPersons);
            }
            continue;
        }

        //move & fight
        std::pair<int, int> shift {0, 0};
        bool isMove = false;
        if (bufferStr == "left" or bufferStr == "l") {
            shift.first = -1;
            isMove = true;
        }
        if (bufferStr == "right" or bufferStr == "r") {
            shift.first = 1;
            isMove = true;
        }
        if (bufferStr == "top" or bufferStr == "t") {
            shift.second = -1;
            isMove = true;
        }
        if (bufferStr == "bottom" or bufferStr == "b") {
            shift.second = 1;
            isMove = true;
        }
        if (isMove){
            int target = move(poolPersons, poolPersons.back(), shift);
            if (target >= 0)
                fight(poolPersons, poolPersons.back(), target);
            break;
        }
    }
}

bool save (const std::string &fileName, const std::vector<Person> &poolPersons){
    std::ofstream file(fileName, std::ios::binary);
    if (file.fail()) {
        std::cout << "Invalid open " << fileName << std::endl;
        file.close();
        return false;
    }
    file << poolPersons.size() << ' ';
    for (const auto &it : poolPersons) {
        savePerson(file, it);
    }
    file.close();
    std::cout << std::endl;
    return true;
}

bool load (const std::string &fileName, std::vector<Person> &poolPersons){
    std::ifstream file(fileName, std::ios::binary);
    if (file.fail()) {
        std::cout << "Invalid open " << fileName << std::endl;
        file.close();
        return false;
    }
    poolPersons.clear();
    int countPersons = poolPersons.size();
    file >> countPersons;
    for (int i = 0; i < countPersons; ++i) {
        poolPersons.push_back(loadPerson(file));
    }
    file.close();
    return true;
}

