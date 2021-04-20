# CS204_hw4
Pattern Search via Stacks



In this homework, you are asked to implement a pattern searching program which makes use of stacks. The pattern to be searched will be a string of bits i.e. a string of 0’s and 1’s of arbitrary length. Your program will search the string within a matrix of bits. This matrix will be input from a file. The search will be snaky such that consecutive bits of the search string may not lie on a line; but may follow a tortuous path. The details of the methods, algorithms and the data structure to be used will be given in the subsequent sections of this homework specification.

The search for a given bit string must always start at (0, 0) cell (upper-left). The flow of search must be toward right (east) or down (south) or mix of these (other directions cannot be used). That means if ith bit of the search string is at (r, c) cell, then you have to consider only (r+1,c) or (r, c+1) cells for (i+1)th bit, not the other neighbors. This way, we can define a set of consecutive cells to represent the search string bits as a path. The purpose of the program is to find such a specific path. There might be more than one possible path; in such a case, finding one of them is sufficient; you do not need to find all.



1. Firstly, you have to focus at the starting cell (0, 0). If the starting element does not allow a path for the searched string (i.e. if the matrix value at (0, 0) is not the 0th element of the search string), you set the flag of (0, 0) to TRUE before checking the rest (i.e. before getting into the loop to check the rest).
2. Then you start to search the rest within a loop. This loop should stop when you find the desired path or the flag of (0, 0) is TRUE.
a. In each step of your search (in the loop), you have to check on a specific element of the matrix (initially it is (0, 0), but at each iteration it may change as explained below). You have to check if the flag of this element is TRUE or FALSE. If it is FALSE and if the matrix value at this element is the same as the corresponding bit in the search string, then it means this position is a candidate path element. In such a case:
i. First you have to push that position on your stack (in order to remember that position later).
ii. You have to check if the entire string has been found.

iii. Else if there still are some bits to search for, you will move toward either right or down to be checked in the next iteration. Of course, this move will be done if the flag of the neighbors is not TRUE (i.e. if not blocked).
iv. Else if both directions are blocked, you should change the flag of the current element to TRUE, since you cannot move forward from it as well and it blocks you. That means, the current cell cannot be on the path and you have backtrack to the previous matched bit. In such a case, you backtrack by popping from the stack.
b. Else if the flag of the current matrix element is TRUE or if the value is not the same as the corresponding bit of the search string, then this position blocks your search. In such a case:
i. first you have to set the flag of this position to TRUE mentioning it is blocked.
ii. You have to backtrack to previous match by popping the last visited cell from the stack.
3. At the end of the loop, either you found path for the search string or it has not been found.
a. If found, the resulting path must be displayed by printing out the row and column indices of the elements in the order that they appear on the path starting from (0, 0). Hint: the elements of the path are already in the stack after the loop, but in reverse order. You will need to reverse the stack content via another stack (pop from one and push to other) and display the content of the reversed stack by popping from it.
b. If not found, you have to display an appropriate message. Please see the sample runs for message format. Understanding that a path is not found is simply by checking the flag of (0,0) element of the matrix. If this flag is TRUE, then a path is not found. This flag may become TRUE either before the loop starts or within the loop by backtracking.
This algorithm is only for one search string; as mentioned previously, you have to be able to search several strings one after another until CTRL-Z is entered.
