redBlackTree

This program was written during my second semester sophomore year for CS 3050,
an advanced algorithm design course taught in C. The goal of this design was to develop
and understanding of tree variations. Input is taken in the form of a text file of integers
or user input from the console, and an in-order traversal, tree height, black height,
and the second largest element are displayed.

Commands:
	F - <filename.txt> - Read values from a file to create a red black tree.
	E ------------------ Enter values to create a red black tree.
	X ------------------ Exit red black tree generator.

Example Input:
	:f numbers.txt
	:E
	:x

Files:
	numbers.txt has been provided using the given example data.

Externally sourced:
	*    Title: Red-Black Tree
	*    Author: Programiz
	*    Date: n/a
	*    Availability: https://www.programiz.com/dsa/red-black-tree
		-> Red-Black Tree Insertion
		-> In-Order Traversal

	*    Title: Write a Program to Find the Maximum Depth or Height of a Tree
	*    Author: n/a
	*    Date: 28 October, 2021
	*    Availability: https://www.geeksforgeeks.org/write-a-c-program-to-find-the-maximum-depth-or-height-of-a-tree/
		-> BST Tree Height 


Known Bugs:
	- Problem displaying In-Order Traversal where garbage is printed 
	  before tree traversal
		Fix: Running the same command again seems to fix this display issue
	- Problem where input of too large length will cause program to crash
		Fix: Use a relatively short list of numbers; this program was created to test
		     specific number sets, so maximum array sizes are not particularly large.
