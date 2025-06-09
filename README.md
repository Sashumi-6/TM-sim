# TM-sim
Turing machine simulator made in C++

# HOW TO USE

    - The Tape:
        The character '\0' denotes the empty cell

    - The Turing Machine:
    
    - instructions.txt
        FORMAT:
            [initial state]|[accept state]|[HALT/Reject state]
            [currect state][tape(k) currentSymbol...]:[successor state][update tape(k) symbol][Direction for tape(k)]
            ...

        example: (for a 2 tape machine)
            q|a|h
            q01:a10NN
            q10:h01NN
        For instructions, '_' denotes an empty cell