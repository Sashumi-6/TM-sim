#ifndef TAPE_H
#define TAPE_H

#include <iostream>
#include <sstream>
#define sout std::cout
#define send std::endl
#define __emptycell '_'


class tape {
    struct tapeCell {
        tapeCell *R, *L;
        char* cellSymbol;

        //Defined such that we can automatically add a *R and *L in case => removes one step (PDA Theory)
        tapeCell(const char& symbol, tapeCell *L = nullptr, tapeCell *R = nullptr)
        : cellSymbol(new char(symbol)), L(L), R(R) {}
        
        ~tapeCell() {
            delete cellSymbol;
            cellSymbol = nullptr;
        }

        //get refrence to current tape cell's symbol
        char& getSymbol() { return *cellSymbol; }
    };

    tapeCell *head;

public:
    tape(const char* input) {
        head = new tapeCell(*input++);
        tapeCell *linkCreate = head;
        while (*input != '\0') {
            linkCreate->R = new tapeCell(*input++, linkCreate);
            linkCreate = linkCreate->R;
        }
    }

    tape() { head = new tapeCell(__emptycell); }

    ~tape() {
        // Take the head all the way to the left
        while (head->L) {
            head = head->L;
        }

        // Start deleting left -> right
        while (head) {
            tapeCell *tmp = head->R;
            delete head;
            head = tmp;
        }
        head = nullptr;
    }

    // if you input anything other than L || R head will stay where it is.
    // This operator moves the head
    void operator[](char d) {
        switch (d) {
            case 'L':
                if (!head->L) { head->L = new tapeCell(__emptycell, nullptr, head); }
                head = head->L;
            break;

            case 'R':
                if (!head->R) { head->R = new tapeCell(__emptycell, head, nullptr); }
                head = head->R;
            break;
        }
    }

    void updateCell(const char &update) { *(head->cellSymbol) = update; }
    const char& getCurrentSymbol() { return *(head->cellSymbol); }

    std::string printTape() {
        std::stringstream ss;
        tapeCell* tmp = head;
        while (tmp->L) tmp = tmp->L; //get to left most

        while (tmp) {
            ss << '[' << *(tmp->cellSymbol) << ']';
            tmp = tmp->R;
        }

        return ss.str();
    }

};

#endif