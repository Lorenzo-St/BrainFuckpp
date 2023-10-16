/**
 * @file BF.cpp
 * @author Lorenzo St. Luce
 * @brief Implementation for interpreter functions
 * @version 0.1
 * @date 2023-10-10
 *
 * @copyright Copyright Lorenzo St. Luce(c) 2023
 *
 */
#include <vector>
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <thread>
#include "BF.hpp"
// I couldn't think of a better place to put the current nameSpace
// if there is a better suggestion please make it or change.
static std::string nameSpace = "";

bool verifyCharacter(char character)
{
  switch (character)
  {
  case ':':
  case '<':
  case '>':
  case '+':
  case '-':
  case '{':
  case '}':
  case '[':
  case ']':
  case '%':
  case '$':
  case '=':
  case '(':
  case ')':
  case ',':
  case '.':
    return true;
  default:
    return false;
  }
}

void leftShift(std::vector<char> const &registers, char **pointer)
{
  if (*pointer != &(*registers.cbegin()))
    (*pointer)--;
}

void rightShift(std::vector<char> const &registers, char **pointer)
{
  if (*pointer != &(*registers.cend()))
    (*pointer)++;
}

void incrament(char &registers)
{
  ++registers;
}
void deincrament(char &registers)
{
  --registers;
}

void DrawRegisters(std::ostream &os, std::vector<char> const &registers, char const *const loc)
{
  const int size = registers.size();
  for (int i = 0; i < size; ++i)
  {
    os << " [" << std::setw(2) << static_cast<int>(registers[i]) << " ] ";
  }
  os << std::endl;
  for (int i = 0; i < size; ++i)
  {
    if (loc == &(*(registers.cbegin() + i)))
      os << std::setw(3) << "   ^   ";
    else
      os << "       ";
  }
  os << std::endl;
}

void DrawFunctions(std::ostream &os, std::unordered_map<std::string, const char *> const &functions)
{
  for (auto &func : functions)
  {
    os << func.first << std::endl;
  }
}

void DrawReturns(std::ostream &os, std::stack<const char *> const &returns)
{
  // make a copy because we can't iterate over a stack
  std::stack<const char *> localCopy = std::stack<const char *>(returns);
  while (localCopy.empty() == false)
  {
    // A char pointer gets streamed out, so we need to make it a non char pointer to write the address
    os << std::hex << reinterpret_cast<const int *>(localCopy.top()) << std::endl;
    localCopy.pop();
  }
  os << std::dec;
}

void readKey(char &dest)
{
  std::cin >> dest;
}

void print(char const &charac)
{
  if (charac == 13 || charac == '\n')
    std::cout << std::endl;
  else
    std::cout << charac;
}

void makeFunction(std::unordered_map<std::string, const char *> &functions, char const *&instrctions)
{
  // function name storage
  std::string name = std::string();
  // whether we are escaped
  bool escaped = false;
  // loop till we find the function start
  // reading the name of the function as we go
  ++instrctions;
  while (*instrctions != '(' || escaped)
  {
    if (*instrctions == '\\')
      escaped = true;
    else
    {

      if (verifyCharacter(*instrctions) == false)
      {
        std::cerr << "YOU FOOL: A function MUST ONLY be named with valid BF characters." << std::endl;
        throw std::invalid_argument("YOU FOOL: A function MUST ONLY be named with valid BF characters.");
      }
      name += *instrctions;
      escaped = false;
    }
    ++instrctions;
  }
  // add the function's location to the functions map
  if (nameSpace != "")
    functions[nameSpace + "::" + name] = instrctions;
  else
    functions[name] = instrctions;

  // move exectution to the end of the function
  while (*instrctions != ')')
    ++instrctions;
}

void jumpFunction(std::unordered_map<std::string, const char *> &functions, std::stack<const char *> &returns, char const *&instrctions)
{

  // name of the function storage
  std::string name = std::string();
  bool escaped = false;
  // read till we find the end of the function name
  ++instrctions;
  while (*instrctions != ')' || escaped)
  {
    if (*instrctions == '\\')
      escaped = true;
    else
    {
      name += *instrctions;
      escaped = false;
    }
    ++instrctions;
  }
  // get the location of the function from the map
  const char *loca = nullptr;
  // check if we are in a nameSpace
  if (nameSpace != "")
  {
    if (name[0] == ':' && name[1] == ':')
    {
      name.replace(0, 2, "");
      loca = functions[name];
    }
    else
    {
      loca = functions[nameSpace + "::" + name];
      if (loca == nullptr)
        loca = functions[name];
    }
  }
  else
    loca = functions[name];

  if (loca == nullptr)
  {
    std::cerr << "Hey fool, You can't call a function that doesn't exist. What do you think will happen? the world might end!!!" << std::endl;
    throw std::invalid_argument("Hey fool, You can't call a function that doesn't exist. What do you think will happen? the world might end!!!");
  }
  // make sure the function is a valid call
  if (loca)
  {
    returns.push(instrctions);
    instrctions = loca;
  }
}

void returnFunction(std::stack<const char *> &returns, char const *&instrctions)
{
  // Just in case
  if (returns.size() > 0)
  {
    // jump back and pop
    instrctions = returns.top();
    returns.pop();
  }
}

void loopStart(std::stack<const char *> &loops, const char *data, const char *&instructions)
{
  if (*data == 0)
    while (*instructions != ']')
      ++(instructions);
  else
    loops.push(instructions);
}

void loopEnd(std::stack<const char *> &loops, const char *data, const char *&instructions)
{
  if (*data <= 0)
    loops.pop();
  else
    instructions = loops.top();
}

void readNameSpace(const char *&instruction)
{
  if ((*instruction + 1) == ':')
    nameSpace = "";
  else
  {
    ++instruction;
    std::string localSpace = "";
    bool skipcheck = false;
    while (*instruction != ':' || skipcheck)
    {
      if (*instruction == '\\')
        skipcheck = true;
      else
        localSpace += *instruction;
      ++instruction;
    }
    nameSpace = localSpace;
  }
}

void evaluateCharacter(
    bool debug,
    std::unordered_map<std::string, const char *> &functions,
    std::stack<const char *> &loopStack,
    std::stack<const char *> &returns,
    std::vector<char> &registers,
    std::vector<char> &parent_registers,
    std::vector<std::thread> &threads,
    const char **instruction,
    char **pointer)
{
  switch (**instruction)
  {
  case '<':
    leftShift(registers, pointer);
    break;
  case '>':
    rightShift(registers, pointer);
    break;
  case '+':
    incrament(**pointer);
    break;
  case '-':
    deincrament(**pointer);
    break;
  case '.':
    print(**pointer);
    break;
  case ',':
    readKey(**pointer);
    break;
  case '[':
    loopStart(loopStack, *pointer, *instruction);
    break;
  case ']':
    loopEnd(loopStack, *pointer, *instruction);
    break;
  case '=':
  {
    makeFunction(functions, *instruction);
    if (debug)
      DrawFunctions(std::cout, functions);
  }
  break;
  case '(':
  {
    jumpFunction(functions, returns, *instruction);
    if (debug)
      DrawReturns(std::cout, returns);
  }
  break;
  case ')':
    if (debug)
      DrawReturns(std::cout, returns);
    returnFunction(returns, *instruction);
    break;
  case '{':
    threads.push_back(std::thread(BF_ThreadFunct, std::ref(registers), std::ref(functions), (*instruction) + 1));
    while (**instruction != '}')
      ++*instruction;
    break;
  case '$':
    registers[0] = **pointer;
    break;
  case '%':
    while (parent_registers[0] != 0)
      ;
    parent_registers[0] = **pointer;
    break;
  case ':':
    readNameSpace(*instruction);
    break;
  }
}

void BF_ThreadFunct(std::vector<char> &topLevelRegisters, std::unordered_map<std::string, const char *> &functions, const char *instructionPointer)
{
  std::stack<const char *> loopStack;
  std::stack<const char *> returns;
  std::vector<char> registers = std::vector<char>(topLevelRegisters);
  std::vector<std::thread> threads;
  char *location = registers.data();

  while (*instructionPointer != '}')
  {
    const char &instruction = *instructionPointer;
    evaluateCharacter(false, functions, loopStack, returns, registers, topLevelRegisters, threads, &instructionPointer, &location);
    ++instructionPointer;
  }
  for (auto &thread : threads)
  {
    thread.join();
  }
}