#include <stack>
#include <vector>
#include <iostream>
#include <unordered_map>

/**
 * @brief Writes register values to the stream provided
 *
 * @param os stream to write to
 * @param registers registers to print
 * @param loc
 */
void DrawRegisters(std::ostream &os, std::vector<char> const &registers, char const *const loc);
/**
 * @brief Write created function names to the stream
 *
 * @param os stream to write to
 * @param functions functiosn to write
 */
void DrawFunctions(std::ostream &os, std::unordered_map<std::string, const char *> const &functions);
/**
 * @brief Write a return stack to the stream
 *
 * @param os stream to write to
 * @param returns stack to write
 */
void DrawReturns(std::ostream &os, std::stack<const char *> const &returns);

/**
 * @brief Shift the register pointer over 1 to the left
 *
 * @param registers the registers, used for bounds checking
 * @param pointer the register pointer being moved
 */
void leftShift(std::vector<char> const &registers, char **pointer);
/**
 * @brief Shift the register pointer over 1 to the right
 *
 * @param registers the registers, used for bounds checking
 * @param pointer the register pointer being moved
 */
void rightShift(std::vector<char> const &registers, char **pointer);
/**
 * @brief Incrament the value at a register
 *
 * @param _register the register being incramented
 */
void incrament(char &_register);
/**
 * @brief Deincrament the value at a register
 *
 * @param register the register being deincramented
 */
void deincrament(char &_register);

void makeFunction(std::unordered_map<std::string, const char *> &functions, char const *&instrctions);
void jumpFunction(std::unordered_map<std::string, const char *> &functions, std::stack<const char *> &returns, char const *&instrctions);
void returnFunction(std::stack<const char *> &returns, char const *&instrctions);

/**
 * @brief Checks a loop condition and starts a loop
 *
 * @param loops the current loop stack
 * @param data the register pointer
 * @param instructions the instructions pointer
 */
void loopStart(std::stack<const char *> &loops, const char *data, const char *&instructions);
/**
 * @brief Checks a loop condition and ends a loop
 *
 * @param loops the current loop stack
 * @param data the register pointer
 * @param instructions the instructions pointer
 */
void loopEnd(std::stack<const char *> &loops, const char *data, const char *&instructions);

/**
 * @brief Read a single keyboard input (instruction: ,)
 *
 * @details This will stomp over whatever is in
 *          the register being reference by dest
 * @param dest the register to read to
 */
void readKey(char &dest);
/**
 * @brief Print the registers value to the console (instruction: .)
 *
 * @param charac the register to write
 */
void print(char const &charac);

/**
 * @brief The function that a thread runs in
 *
 * @param topLevelRegisters the registers of the parent
 * @param functions the functions in the program
 * @param instructionPointer the instructions that the thread will run
 */
void BF_ThreadFunct(std::vector<char> &topLevelRegisters, std::unordered_map<std::string, const char *> &functions, const char *instructionPointer);

/**
 * @brief Evaluate a character and make an action
 *
 * @param debug whether we are in debug mode or not
 * @param functions the functions in the program
 * @param loopStack the current loop stack
 * @param returns the current return stack
 * @param registers the registers of the current thread
 * @param parent_registers the parent threads registers
 * @param threads the current threads child/sub threads
 * @param instruction the current instruction pointer
 * @param pointer the current register pointer
 */
void evaluateCharacter(
    bool debug,
    std::unordered_map<std::string, const char *> &functions,
    std::stack<const char *> &loopStack,
    std::stack<const char *> &returns,
    std::vector<char> &registers,
    std::vector<char> &parent_registers,
    std::vector<std::thread> &threads,
    const char **instruction,
    char **pointer);
