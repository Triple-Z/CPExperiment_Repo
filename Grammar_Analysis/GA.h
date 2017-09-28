//
// Created by triplez on 9/28/17.
//

#ifndef GRAMMAR_ANALYSIS_GA_H
#define GRAMMAR_ANALYSIS_GA_H

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>

/**
 * @class Unit character properties
 */
class Unit {
public:
    std::string value;
    std::string key;
    int line;
    int column;

    void print();
};

/**
 * Print all properties of a unit
 */
void Unit::print() {
    std::cout << "-----------------" << std::endl;
    std::cout << "Value: " << value << std::endl;
    std::cout << "Key: " << key << std::endl;
    std::cout << "Position: [" << line << "," << column << "]" << std::endl;
    std::cout << "-----------------" << std::endl;
}

#endif //GRAMMAR_ANALYSIS_GA_H
