# csci335hp3
A performance comparison between two spellchecking classes.

  To be ran from cmd. First argument should be the dictionary file name ("dictionary.txt"), second
argument in the initial call should be the file to be parsed (provided like the dictionary is "check_it.txt").

  Within the program are two "dictionaries", one whose container is an unordered set, and the other with its ordered
counterpart. Both classes have the same operations and spell checking methods.

Typo Checks
  1) Missing Letter
  2) Additional Letter
  3) Swapped Adjacent Letters
  4) Incorrect Letter 
  
  The program should be able to cover all possible cases with given data, but is made to cease checking for a given typo
should one possible solution be found (to conform to the specifications of the assignment). 

The program will output a .txt files with all detected typos and their possible resolutions (one file for each dictionary).
