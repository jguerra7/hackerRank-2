#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <regex>
using namespace std;

/*
Given a 2D array of digits, try to find the occurrence of a given 2D pattern of digits.
For example, consider the following 2D matrix:

1234567890
0987654321
1111111111
1111111111
2222222222

Assume we need to look for the following 2D pattern:
876543
111111
111111

If we scan through the original array, we observe that the 2D pattern begins at the second
row and the third column of the larger grid (the 8 in the second row and third column of the larger grid
is the top-left corner of the pattern we are searching for).

So, a 2D pattern of P digits is said to be present in a larger grid G, if the latter contains a
contiguous, rectangular 2D grid of digits matching with the pattern P, similar to the example shown above.

Input Format
The first line contains an integer, T, which is the number of test cases.
T test cases follow, each having a structure as described below:

The first line contains two space-separated integers, R and C, indicating the number of
rows and columns in the grid G, respectively.
This is followed by R lines, each with a string of C digits, which represent the grid G.
The following line contains two space-separated integers,  r and c, indicating the number of
rows and columns in the pattern grid .
This is followed by r lines, each with a string of c digits, which represent the pattern P.

Constraints
1 <= T <= 5
1 <= R,r,C,c <= 1000
1 <= r <= R
1 <= c <= C

Test Case Generation
Each individual test case has been generated by first specifying the size ( R and C ) of the large 2D matrix,
and then randomly generating the digits in it. A limited number of digits in the larger matrix may be changed
by the problem setter (no more than 5% of the total number of digits in the matrix). So the larger 2D matrix
is almost-random. The pattern matrix has been manually-curated by the problem setter.

Output Format
Display 'YES' or 'NO', depending on whether (or not) you find that the larger grid G contains the rectangular
pattern R. The evaluation will be case sensitive.

Sample Input

2
10 10
7283455864
6731158619
8988242643
3830589324
2229505813
5633845374
6473530293
7053106601
0834282956
4607924137
3 4
9505
3845
3530
15 15
400453592126560
114213133098692
474386082879648
522356951189169
887109450487496
252802633388782
502771484966748
075975207693780
511799789562806
404007454272504
549043809916080
962410809534811
445893523733475
768705303214174
650629270887160
2 2
99
99
Sample Output

YES
NO
*/

int main() {

  int testCases;
  cin >> testCases;

  for(int i = 0; i < testCases; i++) {

    // Initialize result
    string result = "NO";

    // Regex Matches
    smatch matches;
    smatch innerMatches;
    sregex_iterator end = sregex_iterator();

    // Get the grid
    int rows;
    int columns;
    cin >> rows >> columns;
    vector<string> grid(rows);
    for(int j = 0; j < rows; j++){
      cin >> grid[j];
    }

    // Get the grid to search for
    int testRows;
    int testColumns;
    cin >> testRows >> testColumns;
    vector<regex> testQueries(testRows);
    for(int j = 0; j < testRows; j++) {
      string row;
      cin >> row;
      // This will create a lookahead to make sure we can have
      // overlapping matches. Example stackoverflow question:
      // http://stackoverflow.com/a/20837608/2006429
      testQueries[j] = ("(?="+row+").");
    }

    for(int row = 0; row < rows; row++) {
      string rowText = grid[row];
      sregex_iterator begin = sregex_iterator(rowText.begin(), rowText.end(), testQueries[0]);
      for (sregex_iterator i = begin; i != end; ++i) {
        int numberOfMatches = 1;
        smatch match = *i;
        for (int innerRow = 1 ; innerRow < testRows && row + innerRow < rows; innerRow++) {
          // Try to get a match at this row starting from the place where we had our
          // previous match.
          string testString = grid[row + innerRow].substr(match.position());
          if (regex_search(testString,innerMatches,testQueries[innerRow]) && innerMatches.position() == 0) {
            numberOfMatches++;
          } else {
            break;
          }
        }
        if (numberOfMatches == testRows) {
          result = "YES";
          break;
        }
      }
      if (result.compare("YES") == 0) {
        break;
      }
    }
    cout << result << endl;
  }
  return 0;
}