# Context-free grammar Parser Project






Context Free Grammars (CFGs) are a series of rules organized using a set of variables, terminals, production rules, and a start variable. Chomsky-normal form (CNF) is a specified CFG where every rule is of the form:
```
A -> BC
A -> a
```
Where A, B, and C are all variables and a is a terminal.
Grammars in CNF also can't have the start variable on the right side of any rule, and the rule `X -> ε` is only allowed if X is the start variable.




Our code parses and tests the membership of input in a CNF grammar. The code reads a user-specified file containing the rules for the grammar. It then reads lines from a separate specified file and tests the membership of each line in the grammar. To test the membership of an input, our program uses the algorithm from Sipser's _Introduction to the Theory of Computation_ (3rd edition)




This is a c++ program. Run it using the commands
```
 #!/bin/bash
g++ main.cpp -o main
./main
```


in the terminal window. Input the name of the file containing the rules of the CNF grammar, press enter and then enter the name of the file containing the strings you want to check for membership in the grammar.


