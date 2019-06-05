You will use this exact Makefile for your Homework 2. If you need to change it, please consult with me first.

You can compile everything by typing

make clean
make all

You can compile one program individually by just typing make <Program Name>, for example

make query_tree

By typing

make clean

You delete all .o files and executables.

--Note that file avl_tree_modified.h is not provided.
---------------------------------------------------------
What was completed for the project:
Part 1:
Successfully implemented the big 5.
Implemented two parameter constructor SequenceMap which constructs from two strings
Implemented boolean operator override for < and <<
Implemented merge function that merges two SequenceMap's enzyme_acronyms

Part 2a:
- query_tree.cc
To run:
./query_tree rebase210.txt and then enter these 3 inputs:
CC'TCGAGG
TTA'TAA
TC'C
or type in
./query_tree rebase210.txt < input_part2a.txt

Implemented parser in query_tree.cc that reads in the database file (rebase210.txt) and constructs an AVL tree of the DNA data
Implemented TestTree function to test if that sequence exists in the tree.
Output matches the expected output

Part 2b:
- test_tree.cc
- avl_tree.h

To run: ./test_tree rebase210.txt sequences.txt

Implemented calculateValues (calculates the number of nodes, average depth, average depth to log(n) ratio, and repeats)
Implemented queryAndCount (searches a_tree and counts the total number of recursive calls for all executions of find() )
Implemented removeSequences(removes every other sequence in sequences.txt from the tree and then counts the total number of recursion calls for all executions of remove() )
Output is slightly off from expected output

Part 2c:
- test_tree_mod.cc
- avl_tree_mod.h

To run: ./test_tree_mod rebase210.txt sequences.txt

Implemented double rotations directly instead of calling the two single rotations
Output is slight off from both part b and the expected output
