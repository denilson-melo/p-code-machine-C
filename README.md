# p-code-machine-C
An implementation of a simple P-code machine using C.

# Available Instructions
The project is still in progress, for now it supports the following instructions:
- LIT
- OPR
    - RTN   ``` OPR 0 0 ```
    - ADD   ``` OPR 0 2 ```
    - SUB   ``` OPR 0 3 ```
- LOD
- STO
- INT
- JMP
- JPC

#Compilation
####Linux
Just run the 'make' command on a linux terminal from the main folder, it should be good to go.
####Windows
Copy and paste on a prompt (from the Makefile folder):
```sh
gcc -o main src/main.c src/parsing.c src/pcode.c src/error.c -Wall
```

#Running
The machine must run over a specified input file, containing the instructions:
```
./main examples/t1
or
main.exe examples/t
```

#Examples
I've included some examples to test and see how the machine operates. Currently there's a step-by-step execution

####examples/t1 file
Sums 2+3
####examples/t2 file
Subtracts 20 by 5 until gets to 0
####examples/t3 file
Sums 8+2

If you want to create your own examples, try to follow the current format (no newlines or extra spacing), as it may not work properly. AND PAY ATTENTION TO INFITE LOOPS, luckly you can interrupt them witl CTRL + C.

#Useful Links
[A few p-code machine instructions](http://blackmesatech.com/2011/12/pl0/pl0.xhtml)
[A few step-by-step p-code machine examples](http://blackmesatech.com/2011/12/pl0/index.xhtml)
[Reference code](http://en.wikipedia.org/wiki/P-code_machine)
