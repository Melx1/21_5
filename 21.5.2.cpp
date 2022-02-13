#include <iostream>
#include <map>
#include <string>
#include <windows.h>
/*
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

template <typename T>
void showKeyMap (const std::map<std::string, T> &mapRef) {
    for (const auto &it : mapRef){
        std::cout << it.first << ' ';
    }
}

void showMap (const std::map<std::string, int> &mapRef) {
    for (const auto& it: mapRef)
        std::cout << it.first << "(" << it.second << ") ";
}

template <typename T1, typename T2>
void showKeyMapDifference(const std::map<std::string, T1> &firstMapRef, const std::map<std::string, T2> &secondMapRef) {
    for (const auto &it : firstMapRef){
        if (secondMapRef.count(it.first) == 0)
            std::cout << it.first << ' ';
    }
}

template <typename T>
std::string newType(std::map<std::string, T> &mapRef) {
    std::string bufferStr;
    while (true) {
        std::cout << "Enter a name of the " << typeid(T).name() << R"( or "back":)";
        input(bufferStr);

        //reserve words check
        if (bufferStr == "new" or bufferStr == "exit"){
            std::cout << "Sorry, the name is reserved." << std::endl;
            continue;
        }
        else if (bufferStr == "back"){
            return "back";
        }

        if (!mapRef.empty() and mapRef.count(bufferStr) != 0) {
            std::cout << "The name is already in use." << std::endl << std::endl;
            continue;
        }
        break;
    };

    mapRef.emplace (bufferStr, T());

    return bufferStr;
}


struct RoomType {
    unsigned int areaRoom;

    RoomType () {
        while (true) {
            std::cout << "Enter an area of the room:";
            input(areaRoom);
            break;
        }
    }
};

std::map <std::string, RoomType> RoomTypeMap;


struct FloorType {
    float height;
    std::map <std::string, int> RoomMap;

    FloorType(){
        //height
        while (true) {
            std::cout << "Enter an height of the floor:";
            input(height);
            break;
        }

        //RoomMap
        while (true) {
            std::string bufferStr;
            std::cout << "This floor contains:";
            if (RoomMap.empty())
                std::cout << " nothing";
            else
                showMap(RoomMap);
            std::cout << std::endl;
            while (true) {
                std::cout << "Enter ";
                if (!RoomTypeMap.empty() and RoomMap.size() != RoomTypeMap.size()){
                    std::cout << "a room name from the list (";
                    showKeyMapDifference(RoomTypeMap, RoomMap);
                    std::cout << ")\nor ";
                }
                std::cout << R"("new" or "exit":)";

                input(bufferStr);

                if (bufferStr == "exit"){
                    return;
                }

                if (bufferStr == "new") {
                    //win console colour
                    HANDLE  hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
                    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
                    GetConsoleScreenBufferInfo(hStdout, &csbiInfo);
                    WORD wOldColorAttrs = csbiInfo.wAttributes;
                    SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE);

                    std::cout << "\tRoom designer" << std::endl;
                    bufferStr = newType(RoomTypeMap);

                    SetConsoleTextAttribute(hStdout, wOldColorAttrs);
                    std::cout << "\tFloor designer" << std::endl;
                    continue;
                }

                if (RoomMap.count(bufferStr) != 0) {
                    std::cout << "This rooms already added this floor!" << std::endl;
                    continue;
                }
                if (RoomTypeMap.count(bufferStr) == 0) {
                    std::cout << "This type of room was not created!" << std::endl;
                    continue;
                }

                break;
            };

            unsigned int bufferUI;
            while (true) {
                std::cout << "Enter the number of rooms of this type:";
                input(bufferUI);
                break;
            }

            RoomMap.emplace (bufferStr, bufferUI);
            std::cout << std::endl;
        }
    }
};

std::map <std::string, FloorType> FloorTypeMap;


struct BuildingType {
    unsigned int areaBuilding;
    bool isStove;
    std::map <std::string, int> FloorMap;

    BuildingType(){
        //areaBuilding
        while (true) {
            std::cout << "Enter an area of the building:";
            input(areaBuilding);
            break;
        }

        //isStove
        while (true) {
            std::cout << R"(Enter 0 if building without stove or 1 else with stove:)";
            input(isStove);
            break;
        }

        //FloorMap
        while (true) {
            std::string bufferStr;
            std::cout << "This building contains:";
            if (FloorMap.empty())
                std::cout << " nothing";
            else
                showMap(FloorMap);
            std::cout << std::endl;
            while (true) {
                std::cout << "Enter ";
                if (!FloorTypeMap.empty() and FloorMap.size() != FloorTypeMap.size()){
                    std::cout << "a floor name from the list (";
                    showKeyMapDifference(FloorTypeMap, FloorMap);
                    std::cout << ")\nor ";
                }
                std::cout << R"("new" or "exit":)";

                input(bufferStr);

                if (bufferStr == "exit"){
                    return;
                }

                if (bufferStr == "new") {
                    //win console colour
                    HANDLE  hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
                    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
                    GetConsoleScreenBufferInfo(hStdout, &csbiInfo);
                    WORD wOldColorAttrs = csbiInfo.wAttributes;
                    SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_BLUE);

                    std::cout << "\tFloor designer" << std::endl;
                    bufferStr = newType(FloorTypeMap);

                    SetConsoleTextAttribute(hStdout, wOldColorAttrs);
                    std::cout << "\tBuilding designer" << std::endl;
                    continue;
                }

                if (FloorMap.count(bufferStr) != 0) {
                    std::cout << "This floor already added this building!" << std::endl;
                    continue;
                }

                if (FloorTypeMap.count(bufferStr) == 0) {
                    std::cout << "This type of floor was not created!" << std::endl;
                    continue;
                }

                break;
            };

            unsigned int bufferUI;
            while (true) {
                std::cout << "Enter the number of floors of this type:";
                input(bufferUI);
                break;
            }

            FloorMap.emplace (bufferStr, bufferUI);
            std::cout << std::endl;
        }
    }
};

std::map <std::string, BuildingType> BuildingTypeMap;

struct LandType {
    unsigned int areaLand;
    std::map <std::string, int> BuildingMap;

    LandType(){
        //arealand
        while (true) {
            std::cout << "Enter an area of the land:";
            input(areaLand);
            break;
        }

        //BuildingMap
        while (true) {
            std::string bufferStr;
            std::cout << "This land contains:";
            if (BuildingMap.empty())
                std::cout << " nothing";
            else
                showMap(BuildingMap);
            std::cout << std::endl;
            while (true) {
                std::cout << "Enter ";
                if (!BuildingTypeMap.empty() and BuildingMap.size() != BuildingTypeMap.size()){
                    std::cout << "a building name from the list (";
                    showKeyMapDifference(BuildingTypeMap, BuildingMap);
                    std::cout << ")\nor ";
                }
                std::cout << R"("new" or "exit":)";

                input(bufferStr);

                if (bufferStr == "exit"){
                    return;
                }

                if (bufferStr == "new") {
                    //win console colour
                    HANDLE  hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
                    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
                    GetConsoleScreenBufferInfo(hStdout, &csbiInfo);
                    WORD wOldColorAttrs = csbiInfo.wAttributes;
                    SetConsoleTextAttribute(hStdout, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);

                    std::cout << "\tBuilding designer" << std::endl;
                    bufferStr = newType(BuildingTypeMap);

                    SetConsoleTextAttribute(hStdout, wOldColorAttrs);
                    std::cout << "\tLand designer" << std::endl;
                    continue;
                }

                if (BuildingMap.count(bufferStr) != 0) {
                    std::cout << "This building already added this land!" << std::endl;
                    continue;
                }

                if (BuildingTypeMap.count(bufferStr) == 0) {
                    std::cout << "This type of building was not created!" << std::endl;
                    continue;
                }

                break;
            };

            unsigned int bufferUI;
            while (true) {
                std::cout << "Enter the number of buildings of this type:";
                input(bufferUI);
                break;
            }

            BuildingMap.emplace (bufferStr, bufferUI);
            std::cout << std::endl;
        }
    }
};

std::map <std::string, LandType> LandTypeMap;

struct Village {
    std::string villageName;
    unsigned int amountLand;
    std::multimap <std::string, std::pair<unsigned int, unsigned int>> LandMultimap;

    Village(){
        //villageName
        while (true) {
            std::cout << "Enter a name of your village:";
            input(villageName);
            break;
        }

        //amountLand
        while (true) {
            std::cout << "Enter the amount of land in the village:";
            input(amountLand);
            break;
        }

        //landMultimap
        while (true) {
            std::string bufferStr;
            std::cout << "This village contains:";
            if (LandMultimap.empty())
                std::cout << " nothing";
            else
                for (const auto& it: LandMultimap)
                    std::cout << it.first << "(" << it.second.second << ") ";
            std::cout << std::endl;

            while (true) {
                std::cout << "Enter ";
                if (!LandTypeMap.empty()){
                    std::cout << "a building name from the list (";
                    showKeyMap(LandTypeMap);
                    std::cout << ")\nor ";
                }
                std::cout << R"("new" or "exit":)";

                input(bufferStr);

                if (bufferStr == "exit"){
                    return;
                }

                if (bufferStr == "new") {
                    //win console colour
                    HANDLE  hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
                    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
                    GetConsoleScreenBufferInfo(hStdout, &csbiInfo);
                    WORD wOldColorAttrs = csbiInfo.wAttributes;
                    SetConsoleTextAttribute(hStdout,  FOREGROUND_RED);

                    std::cout << "\tLand designer" << std::endl;
                    bufferStr = newType(LandTypeMap);

                    SetConsoleTextAttribute(hStdout, wOldColorAttrs);
                    std::cout << "\tVillage designer" << std::endl;
                    continue;
                }

                if (LandTypeMap.count(bufferStr) == 0) {
                    std::cout << "This type of land was not created!" << std::endl;
                    continue;
                }

                break;
            };

            unsigned int firstNumber;
            while (true) {
                std::cout << "Enter the first number of the land:";
                input(firstNumber);
                break;
            }

            unsigned int lastNumber;
            while (true) {
                std::cout << "Enter the last number of land of this type:";
                input(lastNumber);
                if (lastNumber < firstNumber){
                    std::cout << "Last number must be greater than or equal to the first number." << std::endl;
                    continue;
                }
                break;
            }

            LandMultimap.emplace (bufferStr, std::pair<unsigned int, unsigned int>(firstNumber, lastNumber - firstNumber + 1));
            std::cout << std::endl;
        }
    }
};

bool isGoodNumbers (const Village & village) {
    bool result = true;
    std::map <unsigned int, unsigned int> valueMap;

    unsigned int checkSum = 0;
    for (const auto &it: village.LandMultimap) {
        valueMap.emplace(it.second.first, it.second.second);
        checkSum += it.second.second;
    }

    if (checkSum != village.amountLand) {
        std::cout << "The amount of land in your model is not equal to the target amount of land." << std::endl;
        result = false;
    }

    std::map<unsigned int, unsigned int>::iterator iter = valueMap.begin();
    while (iter != valueMap.end()) {
        if (iter->first + iter->second != (++iter)->first) {
            std::cout << "Invalid land serial number." << std::endl;
            result = false;
            break;
        }
    }

    return result;
}

bool isGoodHome (const BuildingType &build) {
    bool result = true;

    unsigned int numberFloor = 0;
    for (const auto &itFloor: build.FloorMap) {
        numberFloor += itFloor.second;

        unsigned int numberRoom = 0;
        for (const auto & itRoom: FloorTypeMap[itFloor.first].RoomMap) {
            numberRoom += itRoom.second;
        }
        if (numberRoom < 2 or numberRoom > 4) {
            result = false;
            std::cout << itFloor.first << " has the wrong number of rooms." << std::endl;
            break;
        }
    }

    if (numberFloor < 1 or numberFloor > 3){
        result = false;
        std::cout << "Invalid number of floors." << std::endl;
    }

    return result;
}

int main () {
    Village dachi;

    std::cout << std::endl;
    isGoodNumbers(dachi);

    for (const auto &it : BuildingTypeMap) {
        if (isGoodHome(it.second)) {
            std::cout << it.first << " is home type." << std::endl;
        }
    }
}
*/