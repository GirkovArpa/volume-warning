#include "volume.h"
#include "level.h"
#include <iostream>

// g++ main.cpp volume.cpp level.cpp -lwinmm

int main() {
    std::cout << "Volume: " << volume() << std::endl;
    std::cout << "Level: " << level() << std::endl;
}