#include <stack>
#include <vector>
#include <iostream>
#include <unordered_map>

void DrawRegisters(std::ostream &os, std::vector<char> &registers, char const *const loc);
void DrawFunctions(std::ostream &os, std::unordered_map<std::string, const char *> &functions);
void DrawReturns(std::ostream &os, std::stack<const char *> const &returns);

void leftShift(std::vector<char> &registers, char **pointer);
void rightShift(std::vector<char> &registers, char **pointer);
void incrament(char &registers);
void deincrament(char &registers);
void makeFunction(std::unordered_map<std::string, const char *> &functions, char const *&instrctions);
void jumpFunction(std::unordered_map<std::string, const char *> &functions, std::stack<const char *> &returns, char const *&instrctions);
void returnFunction(std::stack<const char *> &returns, char const *&instrctions);

void loopStart(std::stack<const char *> &loops, const char *data, const char *&instructions);
void loopEnd(std::stack<const char *> &loops, const char *data, const char *&instructions);

void readKey(char &dest);
void print(char const &charac);
void BF_ThreadFunct(std::vector<char> &topLevelRegisters, std::unordered_map<std::string, const char *> &functions, const char *instructionPointer);
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
