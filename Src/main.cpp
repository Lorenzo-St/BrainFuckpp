#include <iostream>
#include <stack>
#include <vector>
#include <fstream>
#include <thread>
#include <chrono>
#include <unordered_map>
#include "BF.hpp"

// BrainFuck programming language
// ----------------------------------------------------------------
// has x amount of registers
// commands are
// > shift right by 1 memory space // Done
//      note: cannot run off send of vector, maybe coult make it add registers
// < shift left by 1 memory space // Done
//      note: cannot run off start of vector, can be used to return to first register
// + add 1 to current memory space // Done
// - subtract 1 from current memory space // Done
// , take input from keyboard // Done
// . print to console // Done
// [ start of loop // Done
// ] if reg 0 is not zero, got back to start of loop, if not continue // Done
// { spawn a thread with the passed instructions or function // Done
// } end of thread
// $ return statement, places the return in register 0 // Done
// % thread return statement, places the current register's value in register 1 of the parent thread // Done
// = function create next is name // Done
//      note: a return value can be determined by placing the data pointer
//            on a specified register, maybe even standardized as register 0
// ( start of function // Done
// ) close function // Done
// -----------------------------

int main(int argc, char **argv)
{
  std::stack<const char *> loopStack;
  std::stack<const char *> returns;
  std::vector<char> registers = std::vector<char>();
  std::unordered_map<std::string, const char *> functions;
  std::vector<std::thread> threads;
  registers.resize(8);
  bool debug = false;
  if (argc < 2)
  {
    std::cerr << "must either pass in a filename or a special command" << std::endl;
    throw std::invalid_argument("must either pass in a filename or a special command");
  }
  std::string instructions;
  for (int i = 1; i < argc; ++i)
  {
    std::string inst = std::string(argv[i]);
    if (inst == "--d")
    {
      debug = static_cast<bool>(std::atoi(argv[i + 1]));
    }
    else if (inst == "--n")
    {
    }
    else if (inst == "--f" || argc == 2)
    {
      std::string token;
      std::ifstream in(argv[i + 1]);
      while (!in.eof())
      {
        in >> token;
        auto lambda = [&](std::string s) -> std::string
        {
          size_t loc = 0;
          while ((loc = s.find('\n')) != std::string::npos)
            s = s.replace(loc, loc + 1, " ");
          return s;
        };
        instructions += lambda(token);
      }
    }
  }

  char *location = registers.data();
  const char *inst = instructions.c_str();
  while (inst != &(*instructions.cend()))
  {
    const char &instruction = *inst;
    if (debug)
    {
      DrawRegisters(std::cout, registers, location);
      std::cout << instruction << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    evaluateCharacter(false, functions, loopStack, returns, registers, registers, threads, &inst, &location);
    ++inst;
  }
  for (auto &thread : threads)
  {
    thread.join();
  }
}
