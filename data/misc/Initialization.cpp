//
// Created by Caleb on 2019-05-07.
//

#include <string>
#include <iostream>

struct PodStruct {
    int a;
    int* b;
    std::string c;
};

std::ostream& operator<< (std::ostream& os, const PodStruct p) {
    os << "PodStruct.a: " << p.a << '\n'
       << "PodStruct.b: " << p.b << '\n'
       << "PodStruct.c: " << '"' << p.c << '"'
       << std::endl;
}


int main() {

    int Aa;
    int Ab(5);
    int Ac{6};
    std::cout << "Aa: " << Aa << std::endl;
    std::cout << "Ab: " << Ab << std::endl;
    std::cout << "Ac: " << Ac << std::endl;


}
