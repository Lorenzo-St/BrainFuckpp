# Welcome to BrainFuck++!

BrainFuck++ (BrainFuckpp) is an open source interpreter for the BrainFuck language. 
The interpreter not only supports standard BrainFuck, but also intends to expand the language
and make it an actually functional programming language

## Implemented instruction
```
 > Shift right by 1 register 
      note: cannot run off the end of the register vector, could maybe make it add registers
 < Shift left by 1 register
      note: cannot run off the start of the register vector, can be used to return to register 0
 + Add 1 to the current register
 - Subtract 1 from the current register
 , Take input from the keyboard into the current register
 . Print register to console 
 [ Start of a loop, if the current register is 0, skip loop
 ] If the current register is not zero, go back to the start of the loop, if not continue 
 { Spawn a thread with the passed instructions
 } End of thread
 $ Function return statement. places current register's value in register 0
 % Thread return statement. places the current register's value in register 0 of the parent thread 
 = Function create next is name 
      note: a return value can be determined by placing the data pointer
            on a specified register, maybe even standardized as register 0
 ( Start of function 
 ) End of function
() Call function, name of function goes inside of () 
 : Denotes a namespace. When used as ':foo:' sets the current active namespace to 'foo'
   When used as '=foo::bar()', it creates a function 'bar' inside the 'foo' namespace
      note: It is legal for a function to have a single ':' in its name, however, that will NOT add
            the function to a namespace, so 'foo:bar' will be different from 'foo::bar'.
```


