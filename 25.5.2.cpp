#include <iostream>
#include <vector>

enum class TypeRoom : char {
    bedroom, kitchen, bathroom, childrens, living
};

struct Room {
    unsigned int area;
    TypeRoom typeRoom;
};

struct Floor {
    std::vector<Floor> roomVct;
    unsigned int area;
    unsigned int height;
};

struct Building {
private:
    bool isDefault = false;
    int defaultCountFloor = 1;
    unsigned int defaultArea = 36;
    bool defaultIsStove = false;

public:
    unsigned int maxArea;
    unsigned int area;
    bool isStove;
    std::vector<Floor> floorVct;

    void defaultBuilding () {
        isDefault = true;
        area = defaultArea;
        isStove = defaultIsStove;
        for (int i = 0; i < defaultCountFloor; i++) {
            floorVct.push_back(Floor());
        }
    }

    Building(unsigned int landArea, bool defaultCreate = false) {

    }
};

struct Land {
private:
    bool isDefault = false;
    int defaultCountBuilding = 1;
    unsigned int defaultArea = 600;

public:
    unsigned int countBuilding; //may be 0
    unsigned int area; //min 1
    std::vector<Building> buildingVct;

    void defaultLand () {
        isDefault = true;
        countBuilding = defaultCountBuilding;
        area = defaultArea;
        for (int i = 0; i < countBuilding; i++) {
            buildingVct.push_back(Building(area, true));
        }
    }

    Land(bool defaultCreate = false) {
        if (!defaultCreate) {
            countBuilding = 0;
            while (true) {
                std::cout << "Enter the count of buildings or '0' for create default land: ";
                std::cin >> countBuilding;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Entered error. Try again! \n";
                    continue;
                }
                break;
            }

            if (countBuilding == 0) {
                defaultLand();
                return;
            }

            while (true) {
                unsigned int bufferArea = 0;
                std::cout << "Enter the area of land: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> bufferArea;
                if (std::cin.fail()) {
                    std::cout << "Entered error. Try again! \n";
                    continue;
                }
                if (bufferArea < 1) {
                    std::cout << bufferArea << " - invalid value. Try again! \n";
                    continue;
                }
                area = bufferArea;
                break;
            }

            for (int i = 0; i < countBuilding; i++) {
                buildingVct.push_back(Building(true, area));
            }
        } else
            defaultLand();
    }
};

struct Village {
private:
    bool isDefault = false;
    int defaultCountLand = 5;

public:
    unsigned int countLand; // min 1 land into village
    unsigned int area;
    std::vector<Land> landVct;

    Village() {
        while (true) {
            std::cout << "Enter the count of land or '0' for create default village: ";
            std::cin >> countLand;
            if (std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                std::cout << "Entered error. Try again! \n";
                continue;
            }
            break;
        }

        if (countLand == 0) {
            isDefault = true;
            countLand = defaultCountLand;
        }

        area = 0;
        for (int i = 0; i < countLand; i++){
            landVct.push_back(Land(isDefault));
            area += landVct[i].area;
        }
    }
};

int main () {
    Village villariba;
}