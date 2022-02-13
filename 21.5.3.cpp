#include <iostream>
#include <cmath>
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

struct VectorXY {
    double x;
    double y;

    friend std::ostream& operator<< (std::ostream &out, const VectorXY &vct);
    friend std::istream& operator>> (std::istream &in, VectorXY &vct);
};

std::ostream& operator<< (std::ostream &out, const VectorXY &vct) {
    out << "(" << vct.x << ", " << vct.y << ")";
    return out;
}

std::istream& operator>> (std::istream &in, VectorXY &vct) {
    in >> vct.x >> vct.y;
    return in;
}

VectorXY add (const VectorXY &vct1,const VectorXY &vct2) {
    VectorXY result{};
    result.x = vct1.x + vct2.x;
    result.y = vct1.y + vct2.y;
    return result;
}

VectorXY subtract (const VectorXY &vct1, const VectorXY &vct2) {
    VectorXY result{};
    result.x = vct1.x - vct2.x;
    result.y = vct1.y - vct2.y;
    return result;
}

VectorXY scale (const VectorXY &vct1, double scl) {
    VectorXY result{};
    result.x = vct1.x * scl;
    result.y = vct1.y * scl;
    return result;
}

double length (const VectorXY &vct) {
    return hypot(vct.x, vct.y);
}

VectorXY normalize(const VectorXY &vct) {
    double len = length(vct);
    VectorXY result{};
    result.x = vct.x / len;
    result.y = vct.y / len;
    return result;
}

int main () {
    int command;
    while (true) {
        std::cout << "Enter the command (add - 1, subtract - 2, scale - 3, length - 4, normalize - 5):";
        input(command);
        if (command < 1 or command > 5){
            std::cout << "Unknown command.";
            continue;
        }
        break;
    }


    VectorXY firstVctXY {};
    std::cout << "Enter vector:";
    input(firstVctXY);

    switch (command) {
        case 1: {
            VectorXY secondVctXY {};
            std::cout << "Enter another vector:";
            input(secondVctXY);
            std::cout << "Result:" << add(firstVctXY, secondVctXY) << std:: endl;
            break;
        }
        case 2:{
            VectorXY secondVctXY {};
            std::cout << "Enter another vector:";
            input(secondVctXY);
            std::cout << "Result:" << subtract(firstVctXY, secondVctXY) << std:: endl;
            break;
        }
        case 3:{
            double scl;
            std::cout << "Enter scale:";
            input(scl);
            std::cout << "Result:" << scale(firstVctXY, scl) << std:: endl;
            break;
        }
        case 4:{
            std::cout << "Result:" << length(firstVctXY) << std:: endl;
            break;
        }
        case 5:{
            std::cout << "Result:" << normalize(firstVctXY) << std:: endl;
            break;
        }
    }

    return 0;
};
*/