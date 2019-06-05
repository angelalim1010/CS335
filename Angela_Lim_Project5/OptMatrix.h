//Angela Lim
//CS 335
//Header file that includes the function that prints the parenthesis
//Second function finds the optimal number of multiplcation
#ifndef OPTMATRIX_H
#define OPTMATRIX_H
#include <iostream>
#include <vector>
#include<stdio.h>
#include <string>
using namespace std;

//prints the optimal parenthesis for a matrix
void PrintParenthesis(int i, int j, int n,  int *parenthesis, char &name){
//if there's only one matrix in the current segment
    if(i == j){
      cout << name++;
      return;
    }
    cout << "(";
    //Recusrively put the parenthesis around subsegments from i to segement [i][j]
    PrintParenthesis(i, *((parenthesis + i * n)+ j), n, parenthesis, name);
    //Recusrively put parenthesis around segements from [i][j] to j
    PrintParenthesis(*((parenthesis + i * n)+ j) + 1, j, n, parenthesis, name);
    cout << ")";
  }

//function that finds the optimal number of multiplication
int OptMatrix( const vector<int> & c, int n )
{   //Allocates one extra row and column but [0][0] isn't used
    int matrix[n][n];

    // Stores where the brackets are placed;
    int parenthesis[n][n];
    //for one matrix the cost is 0
    for(int i = 1; i < n; i++){
      matrix[i][i] = 0;
    }
    //@param l = chain length
    for(int l = 2; l < n; l++){
      for(int i = 1; i < n-l+1; i++){
        int j = i + l - 1;
        matrix[i][j] = INT_MAX;
        for(int k = i; k <= j - 1; k++){
            //q is cost per scalar multiplication
          int q = matrix[i][k] + matrix[k+1][j] + c[i-1] * c[k] * c[j];
          if(q < matrix[i][j]){
            matrix[i][j] = q;
            //each [i,j] = k shows where to split the product array
            //i, i+i, ..., j is the optimal number of multiplications
            parenthesis[i][j] = k;
          }
        }
      }
    }
  char name = 'A';
  cout << "The optimal parenthetical ordering is : ";
  PrintParenthesis(1, n-1, n, (int *)parenthesis, name);
  cout << endl;
  return matrix[1][n-1];
}


#endif
