# TM-sim

A modern, easy-to-use Turing Machine simulator written in C++.

---

## Features
- Supports multi-tape Turing machines
- Customizable instruction set via `instructions.txt`
- Clear tape visualization
- Simple command-line interface

---

## How to Use

### The Tape
- The character `'_'` denotes the empty cell on the tape.
- Tapes are dynamically extended as the head moves left or right.

### The Turing Machine
- The machine reads its configuration and instructions from `instructions.txt`.
- You can specify the number of tapes and the input word in `main.cpp`.

### `instructions.txt` Format
- **Header:**
  ```
  [initial state]|[accept state]|[HALT/Reject state]
  ```
- **Instructions:**
  ```
  [current state][tape1 symbol][tape2 symbol]...:[next state][write symbol1][write symbol2]...[move1][move2]...
  ```
  - For a 2-tape machine, an example:
    ```
    q|a|h
    q01:a10NN
    q10:h01NN
    ```
  - Use `'_'` to denote an empty cell.
  - Moves: `L` (left), `R` (right), `N` (no move)

---

## Build & Run

1. **Build:**
   ```bash
   make
   ```
2. **Run:**
   ```bash
   make run
   ```

---

## Example Output
```
========================================
Initial configuration
========================================
TAPE 1:
[1][0][1][0][0][1][1]
TAPE 2:
[_][_][_][_][_][_][_]
...
```

---

## Customization
- Edit `main.cpp` to change the input word or number of tapes.
- Edit `instructions.txt` to define your Turing machine's logic.

---

## License
MIT License