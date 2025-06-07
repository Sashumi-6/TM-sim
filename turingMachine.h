#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>
#include "tape.h"

#define accept '\a'
#define sout std::cout
#define send std::endl

class TM {
    int tapeCount;
    char state;
    tape **tapes;

public:
    TM(const char* input, int &tapeCount) {
        this->tapeCount = (tapeCount <= 0) ? 1 : tapeCount;
        tapes = new tape*[tapeCount];

        for (int i = 0 ; i < tapeCount ; i++) {
            if (i == 0) tapes[i] = new tape(input);
            else tapes[i] = new tape();
        }
    }

    ~TM() {
        for (int i = 0 ; i < tapeCount ; i++) {
            delete tapes[i];
        }
        delete[] tapes;
    }

    // instructions is the instructions.txt file
    int execute(std::string instructions) {
        readInstructions(instructions);

        return 0;
    }

    void readInstructions(std::string filename) {
        std::fstream fs(filename.c_str());

    }

    std::string printTapeN(int n) {
        if (n < 0) n = 0;
        if (n >= tapeCount) n = tapeCount-1;

        return tapes[n]->printTape();
    }

    std::string printAllTapes() {
        std::stringstream ss;
        for (int i = 0 ; i < tapeCount ; i++) {
            ss << "TAPE " << (i + 1) << ":\n";
            ss << printTapeN(i);
            ss << "\n";
        }

        return ss.str();
    }

};

#endif