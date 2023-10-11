# Welcome to BrainFuck++!

BrainFuck++ (BrainFuckpp) is an open source interpreter for the BrainFuck language. 
The interpreter not only supports standard BrainFuck, but also intends to expand the language
and make it an actually functional programming language

## Implemented instruction
```
 > shift right by 1 register 
      note: cannot run off send of vector, maybe coult make it add registers
 < shift left by 1 register
      note: cannot run off start of vector, can be used to return to first register
 + add 1 to current register
 - subtract 1 from current register
 , take input from keyboard into current register
 . print register to console 
 [ start of loop, if current register is 0, skip loop
 ] if current register is not zero, got back to start of loop, if not continue 
 { spawn a thread with the passed instructions or function 
 } end of thread
 $ return statement, places the return in register 0 
 % thread return statement, places the current register's value in register 0 of the parent thread 
 = function create next is name 
      note: a return value can be determined by placing the data pointer
            on a specified register, maybe even standardized as register 0
 ( start of function 
 ) close function
```
