#include <iostream>
#include "turingMachine.h"
#define sout std::cout
#define send std::endl

int main() {
    const char* word = "1010011";
    int tapeCount = 2;
    TM tm(word, tapeCount, "instructions.txt");
    
    sout << "\n========================================\nInitial configuration\n========================================\n" << tm.printAllTapes() << send;
    if (tm.execute()) {
        sout << "========================================\nMachine terminates in accept state\n========================================" << send;
    } else {
        sout << "========================================\nMachine terminates in halt/reject state\n========================================" << send;
    }
    sout << tm.printAllTapes() << send;

    return 0;
}