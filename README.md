# Welcome to BrainFuck++!

BrainFuck++ (BrainFuckpp) is an open source interpreter for the BrainFuck language. 
The interpreter not only supports standard BrainFuck, but also intends to expand the language
and make it an actually functional programming language

## Implemented instruction
```
 > shift right by 1 register 
      note: cannot run off send of vector, maybe could make it add registers
 < shift left by 1 register
      note: cannot run off start of vector, can be used to return to register 0
 + add 1 to current register
 - subtract 1 from current register
 , take input from keyboard into current register
 . print register to console 
 [ start of loop, if current register is 0, skip loop
 ] if current register is not zero, got back to start of loop, if not continue 
 { spawn a thread with the passed instructions or function 
 } end of thread
 $ return statement, places current register's value in register 0
 % thread return statement, places the current register's value in register 0 of the parent thread 
 = function create next is name 
      note: a return value can be determined by placing the data pointer
            on a specified register, maybe even standardized as register 0
 ( start of function 
 ) close function
() Call function, name of function goes inside of () 
 : Denotes a namespace. When used as ':foo:' sets the current active namespace to 'foo'
   When used as '=foo::bar()', it creates a function 'bar' inside the 'foo' namespace
      note: It is legal for a function to have a single ':' in it's name, however, that will NOT add
            the function to a namespace, so 'foo:bar' will be different from 'foo::bar'.
```


