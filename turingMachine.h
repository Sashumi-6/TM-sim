#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include <cassert>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include "tape.h"

#define sout std::cout
#define send std::endl

class TM {
    int tapeCount;
    tape **tapes;
    std::string *instructions;
    int i_size = 0;
    char baseStates[3];
    char currentState;

    void LoadInstructions(std::string filename) {
        std::fstream fs(filename.c_str());
        if (fs.eof()) assert("Please insert instructions");
        std::stringstream ss;
        std::string line;

        std::getline(fs, line, '|');
        currentState = baseStates[0] = line[0]; //initial
        std::getline(fs, line, '|');
        baseStates[1] = line[0]; //accept
        std::getline(fs, line);
        baseStates[2] = line[0]; //halt

        int count = 0;
        while (std::getline(fs, line)) {
            if (line.empty()) continue;
            ss << line + "\n";
            count++;
        }

        i_size = count;
        instructions = new std::string[count];
        for (int i = 0 ; i < count ; i++) {
            ss >> instructions[i];
        }
    }

    std::string getCurrentConfiguration() {
        std::string config(1, currentState);
        for (int i = 0 ; i < tapeCount ; i++) {
            config += tapes[i]->getCurrentSymbol();
        }
        return config;
    }

    int executeInstruction() {
        std::string currentConfig = getCurrentConfiguration();

        int instructionIdx = -1;
        for (int i = 0 ; i < i_size ; i++) {
            if (currentConfig != instructions[i].substr(0, tapeCount + 1)) continue;
            instructionIdx = i;
            break;
        }
        if (instructionIdx == -1) {
            sout << "No such instruction exists for \"" << currentConfig << "\"" << send;
            system(0);
        }
        sout << instructions[instructionIdx] << send;

        std::string update = instructions[instructionIdx].substr(tapeCount + 2);
        currentState = update[0];
        int currentTape = 0;
        bool successorSymbolSection = true;
        for (char s : update) {
            if (s == currentState) continue;

            if (successorSymbolSection) {
                tapes[currentTape++]->updateCell(s);
                if (currentTape == tapeCount) {
                    currentTape = 0;
                    successorSymbolSection = false;
                }
            } else { tapes[currentTape++]->moveHead(s); } //using this bc clang doesnt like or trust me
        }

        return 1;
    }

public:
    TM(const char* input, int &tapeCount, std::string filePath) : instructions(nullptr) {
        this->tapeCount = (tapeCount <= 0) ? 1 : tapeCount;
        tapes = new tape*[tapeCount];

        for (int i = 0 ; i < tapeCount ; i++) {
            if (i == 0) tapes[i] = new tape(input);
            else tapes[i] = new tape();
        }

        currentState = '\0'; // current state = null ie. havent set current state
        LoadInstructions(filePath);
    }

    ~TM() {
        for (int i = 0 ; i < tapeCount ; i++) {
            delete tapes[i];
        }
        delete[] tapes;
        delete[] instructions;
    }

    // instructions is the instructions.txt file
    int execute() {
        while (currentState != baseStates[1] && currentState != baseStates[2]) {
            executeInstruction();
        }

        if (currentState == baseStates[1]) return 1;
        return 0;
    }

    int executeOneStep() {
        executeInstruction();
        if (currentState == baseStates[1]) return 1;
        return 0;
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